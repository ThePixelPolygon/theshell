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

#ifndef LOCATIONDAEMON_H
#define LOCATIONDAEMON_H

#include <QObject>
#include <QDBusMessage>
#include <QDBusReply>
#include <QDebug>
#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusConnectionInterface>
#include <QMutex>
#include <QMutexLocker>
#include <tpromise.h>

struct Geolocation {
    double latitude;
    double longitude;
    double accuracy;
    double altitude;
    double speed;
    double heading;
    QString description;
    QDateTime timestamp;

    bool resolved = false;
};

class LocationDaemon : public QObject
{
        Q_OBJECT
    public:
        explicit LocationDaemon(QObject *parent = nullptr);

    signals:

    public slots:
        bool startListening();
        bool stopListening();
        tPromise<Geolocation>* singleShot();

    private slots:
        void locationUpdated();

    private:
        QDBusObjectPath geoclueClientPath;
        QDBusInterface* clientInterface = nullptr;
        int listeningTimes = 0;

        QMutex listeningMutex;
};

#endif // LOCATIONDAEMON_H