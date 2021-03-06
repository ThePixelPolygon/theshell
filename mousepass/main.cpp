/****************************************
 *
 *   theShell - Desktop Environment
 *   Copyright (C) 2019 Victor Tran
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * *************************************/

#include <QCoreApplication>
#include <QRandomGenerator>
#include <QFile>
#include <QDir>
#include <QFile>
#include <unistd.h>
#include <polkit-qt5-1/PolkitQt1/Authority>
#include <iostream>

bool checkPolkitAuthorization() {
    //Check Polkit authorization
    pid_t parentPid = getppid();
    PolkitQt1::Authority::Result r = PolkitQt1::Authority::instance()->checkAuthorizationSync("org.thesuite.theshell.configure-mouse-password", PolkitQt1::UnixProcessSubject(parentPid), PolkitQt1::Authority::None);

    if (r == PolkitQt1::Authority::No) {
        return false;
    } else if (r == PolkitQt1::Authority::Challenge) {
        PolkitQt1::Authority::Result r = PolkitQt1::Authority::instance()->checkAuthorizationSync("org.thesuite.theshell.configure-mouse-password", PolkitQt1::UnixProcessSubject(parentPid), PolkitQt1::Authority::AllowUserInteraction);
        if (r != PolkitQt1::Authority::Yes) {
            return false;
        }
    }

    return true;
}

bool setMousePassword(QString mousePassword, QString passwordFile) {
    if (!checkPolkitAuthorization()) return false;

    QByteArray salt = "$1$";

    const char* saltCharacters = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < 8; i++) {
        salt.append(saltCharacters[QRandomGenerator::securelySeeded().bounded(quint32(0), static_cast<quint32>(strlen(saltCharacters)))]);
    }

    QString hashedPassword = QString::fromLocal8Bit(crypt(mousePassword.toLocal8Bit().data(), salt.data()));
    QFile mousepassfile(passwordFile);
    if (!mousepassfile.open(QFile::WriteOnly)) return false;

    mousepassfile.write(hashedPassword.toUtf8());
    mousepassfile.close();
    return true;
}

bool removeMousePassword(QString passwordFile) {
    if (!checkPolkitAuthorization()) return false;

    QFile mousepassfile(passwordFile);
    return mousepassfile.remove();
}

int main(int argc, char *argv[])
{
    QCoreApplication::setSetuidAllowed(true);
    QCoreApplication a(argc, argv);

    QString setMousePass = "";
    QString mousePassFile = "";
    bool removePass = false;
    for (QString arg : a.arguments()) {
        if (arg.startsWith("--set=")) {
            //Set mouse password
            setMousePass = arg.mid(arg.indexOf("=") + 1);
        } else if (arg.startsWith("--passfile=")) {
            mousePassFile = arg.mid(arg.indexOf("=") + 1);
        } else if (arg == "--remove") {
            removePass = true;
        }
    }

    if (setMousePass != "" && removePass) {
        std::cout << "Can't remove and set mouse password at the same time.\n";
        return 1;
    }

    if (setMousePass != "") {
        if (mousePassFile == "") {
            std::cout << "Mouse password file not specified.\n";
            return 1;
        }

        if (!setMousePassword(setMousePass, mousePassFile)) {
            std::cout << "Could not set mouse password.\n";
            return 1;
        }
    } else if (removePass) {
        if (mousePassFile == "") {
            std::cout << "Mouse password file not specified.\n";
            return 1;
        }

        if (!removeMousePassword(mousePassFile)) {
            std::cout << "Could not remove mouse password.\n";
            return 1;
        }
    }

    return 0;
}
