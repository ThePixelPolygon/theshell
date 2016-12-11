#ifndef DBUSEVENTS_H
#define DBUSEVENTS_H

#include <QObject>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QProcess>
#include <QApplication>
#include <QDBusObjectPath>
#include <QDBusReply>
#include <QDebug>
#include <QDBusInterface>
#include <QSettings>
#include <QTimer>
#include "notificationdbus.h"
#include "newmedia.h"

class DbusEvents : public QObject
{
    Q_OBJECT
public:
    explicit DbusEvents(NotificationDBus* notifications, QObject *parent = 0);

signals:

public slots:
    void LockScreen();

    void UnlockScreen();

    void NewUdisksInterface(QDBusObjectPath path);

    void DetectNewDevices();

private slots:
    void SleepingNow();

private:
    QProcess* LockScreenProcess = NULL;

    NotificationDBus* notificationEngine;
    QSettings settings;
    QStringList connectediOSDevices;
};

#endif // DBUSEVENTS_H
