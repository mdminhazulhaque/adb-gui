#include "adb.h"

namespace adb {

bool pull(QString remotePath, QString localPath)
{
    QString pullCmd = QString("pull %1 %2").arg(remotePath).arg(localPath);
    run_adb_proc(pullCmd);
    return QFile(localPath).exists();
}

QString apk_path(QString packageName)
{
    QString apkPath = run_adb_proc("shell pm path " + packageName);
    apkPath.remove("package:");
    return apkPath.trimmed();
}

int device_count()
{
    QString devices = run_adb_proc("devices -l");
    int lines = devices.count(QLatin1Char('\n'));

    return lines - 2;
}

QString run_adb_proc(QString params)
{
    QProcess process;

    process.start("/usr/bin/adb", params.split(" "), QProcess::ReadOnly);
    process.waitForFinished();

    QString result = process.readAll();
    process.close();

    return result;
}

DeviceList device_list()
{
    DeviceList deviceList;

    QStringList deviceListData = run_adb_proc("devices -l").split(QLatin1Char('\n'));

    //return deviceList;
    deviceListData.pop_back();
    deviceListData.pop_front();

    for(int d=0; d<deviceListData.size(); d++)
    {
        QString deviceData = deviceListData[d];

        if(deviceData.isEmpty())
            continue;

        deviceData.replace(QRegExp("[\\s\\n\\r]+"), " ");

        QStringList dataList = deviceData.split(" ");

        Device dev;
        dev.serialNumber = dataList[0];
        //dev.productName = dataList[3].remove("product:");
        dev.modelName = dataList[4].remove("model:");
        //dev.deviceName = dataList[5].remove("device:");

        deviceList.push_back(dev);
    }

    return deviceList;
}

}
