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

#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QDialog>
#include <QSettings>
#include <QMenu>
#include <QDesktopWidget>
#include <QSvgRenderer>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QPaintEvent>
#include "choosebackground.h"

class ChooseBackground;
class MainWindow;

namespace Ui {
class Background;
}

struct BackgroundPrivate;
class Background : public QDialog
{
    Q_OBJECT

    public:
        explicit Background(MainWindow* mainwindow, bool imageGetter, QRect screenGeometry, QWidget *parent = 0);
        ~Background();

        void show();

    public slots:
        void changeBackground();

        void toggleChangeBackground();

        void showCommunityBackgroundSettings(bool shown);

    signals:
        void setAllBackgrounds(QString background);

        void reloadBackground();

    private slots:
        void on_actionOpen_Status_Center_triggered();

        void on_actionOpen_theShell_Settings_triggered();

        void on_actionChange_Background_triggered();

        void on_Background_customContextMenuRequested(const QPoint &pos);

        void on_tryReloadBackgroundButton_clicked();

        void on_backgroundList_clicked(const QModelIndex &index);

        void on_backButton_clicked();

        void on_showImageInformationBox_toggled(bool checked);

        void on_stretchFitButton_toggled(bool checked);

        void on_zoomCropButton_toggled(bool checked);

        void on_centerButton_toggled(bool checked);

        void on_tileButton_toggled(bool checked);

        void on_zoomFitButton_toggled(bool checked);

    private:
        Ui::Background *ui;
        BackgroundPrivate* d;

        void reject();

        bool eventFilter(QObject* watched, QEvent* event);
        void paintEvent(QPaintEvent* event);
        void resizeEvent(QResizeEvent* event);
};

#endif // BACKGROUND_H
