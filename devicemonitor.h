#ifndef DEVICEMONITOR_H
#define DEVICEMONITOR_H

#include <QThread>
#include "adb.h"

class DeviceMonitor : public QThread
{
    Q_OBJECT
public:
    explicit DeviceMonitor(QObject *parent = 0);
    void run();

signals:

public slots:

};

#endif // DEVICEMONITOR_H
