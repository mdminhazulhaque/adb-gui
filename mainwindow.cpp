#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("adb-gui");
    ui->progressBackup->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::adb_pull(QString remotePath, QString localPath)
{
    QProcess process;
    QString args = QString("pull %1 %2").arg(remotePath).arg(localPath);

    //qDebug() << args;

    process.start("/usr/bin/adb", args.split(" "), QProcess::ReadOnly);
    process.waitForFinished();

    return true;
}

QString MainWindow::adb_apk_path(QString packageName)
{
    QProcess process;
    QString args = "shell pm path " + packageName;

    process.start("/usr/bin/adb", args.split(" "), QProcess::ReadOnly);
    process.waitForFinished();

    QString apkPath = process.readAll();
    apkPath.remove("package:");

    return apkPath.trimmed();
}

void MainWindow::on_btnLoad_clicked()
{
    QProcess process;
    QString args = "shell pm list packages -3";

    process.start("/usr/bin/adb", args.split(" "), QProcess::ReadOnly);
    process.waitForFinished();

    while(process.canReadLine())
    {
        QString line = process.readLine().trimmed();
        line.remove("package:");

        QListWidgetItem *listItem = new QListWidgetItem(line, ui->packageList);
        listItem->setIcon(QIcon::fromTheme("application-archive"));
        listItem->setCheckState(Qt::Unchecked);
        ui->packageList->addItem(listItem);

    }
}

void MainWindow::on_btnMarkAll_clicked()
{
    for(int i=0; i<ui->packageList->count(); i++)
    {
        QListWidgetItem *item = ui->packageList->item(i);
        item->setCheckState(Qt::Checked);
    }

}

void MainWindow::on_btnUnmarkAll_clicked()
{
    for(int i=0; i<ui->packageList->count(); i++)
    {
        QListWidgetItem *item = ui->packageList->item(i);
        item->setCheckState(Qt::Unchecked);
    }
}

void MainWindow::on_btnBackup_clicked()
{
    //QProgressDialog progress("Task in progress...", "Cancel", 0, ui->packageList->count(), this);
    //progress.setWindowModality(Qt::WindowModal);
    //progress.show();

    int checked = 0;

    for(int i=0; i<ui->packageList->count(); i++)
    {
        QListWidgetItem *item = ui->packageList->item(i);
        if(item->checkState() == Qt::Unchecked)
            continue;
        else
            checked++;
    }

    ui->progressBackup->setValue(0);
    ui->progressBackup->setMinimum(0);
    ui->progressBackup->setMaximum(checked-1);
    ui->progressBackup->show();

    for(int i=0, c=0; i<ui->packageList->count(); i++)
    {
        QListWidgetItem *item = ui->packageList->item(i);

        if(item->checkState() == Qt::Unchecked)
            continue;

        QString apkPath = adb_apk_path(item->text());
        adb_pull(apkPath, "/home/minhaz");
        ui->progressBackup->setValue(++c);
    }

    ui->progressBackup->hide();
    //progress.done(ui->packageList->count());
}
