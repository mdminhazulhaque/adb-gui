#ifndef ADB_H
#define ADB_H

#include <QObject>
#include <QProcess>
#include <QFile>
#include <QDebug>

namespace adb {

typedef struct {
    QString serialNumber;
    //QString productName;
    QString modelName;
    //QString deviceName;
} Device;

typedef QVector<Device> DeviceList;

bool        pull(QString remotePath, QString localPath);
int         device_count();
DeviceList  device_list();
QString     apk_path(QString packageName);
QString     run_adb_proc(QString params);

}
#endif // ADB_H
