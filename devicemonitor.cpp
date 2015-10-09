#include "devicemonitor.h"

DeviceMonitor::DeviceMonitor(QObject *parent) :
    QThread(parent)
{
}

void DeviceMonitor::run()
{
    adb::DeviceList deviceInfo = adb::device_list();




}
