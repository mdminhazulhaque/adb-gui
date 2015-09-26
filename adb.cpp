#include "adb.h"

bool ADB::adb_pull(QString remotePath, QString localPath)
{
    QProcess process;
    QString args = QString("pull %1 %2").arg(remotePath).arg(localPath);

    //qDebug() << args;

    process.start("/usr/bin/adb", args.split(" "), QProcess::ReadOnly);
    process.waitForFinished();

    return true;
}

QString ADB::adb_apk_path(QString packageName)
{
    QProcess process;
    QString args = "shell pm path " + packageName;

    process.start("/usr/bin/adb", args.split(" "), QProcess::ReadOnly);
    process.waitForFinished();

    QString apkPath = process.readAll();
    apkPath.remove("package:");

    return apkPath.trimmed();
}

bool ADB::adb_is_device_available()
{
    QProcess process;
    QString args = "devices";

    process.start("/usr/bin/adb", args.split(" "), QProcess::ReadOnly);
    process.waitForFinished();

    QString devices = process.readAll();
    int lines = devices.count(QLatin1Char('\n'));

    if(lines > 2)
        return true;
    else
        return false;
}
