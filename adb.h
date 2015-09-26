#ifndef ADB_H
#define ADB_H

#include <QObject>
#include <QProcess>
#include <QDebug>

class ADB
{
public:
    //explicit ADB(QObject *parent = 0);
    static bool adb_pull(QString remotePath, QString localPath);
    static QString adb_apk_path(QString packageName);
    static bool adb_is_device_available();
};

#endif // ADB_H
