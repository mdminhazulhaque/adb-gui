#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Android Debug Bridge - Frontend");

    QTimer timerDeviceMonitor;
    connect(&timerDeviceMonitor, SIGNAL(timeout()), this, SLOT(monitorDevice()));
    timerDeviceMonitor.start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::monitorDevice()
{
    qDebug() << "run";
}

void MainWindow::on_btnLoad_clicked()
{
    ui->packageList->clear();

    if(adb::device_count() < 1)
    {
        QMessageBox::critical(this,
                              "Error",
                              "No device connected");
        return;
    }

    QProcess process;
    QString args = "shell pm list packages -3";

    process.start("/usr/bin/adb", args.split(" "), QProcess::ReadOnly);
    process.waitForFinished();

    while(process.canReadLine())
    {
        QString line = process.readLine().trimmed();

        if(line.startsWith("* daemon"))
            continue;

        line.remove("package:");

        QListWidgetItem *listItem = new QListWidgetItem(line, ui->packageList);
        listItem->setIcon(QIcon::fromTheme("application-x-archive"));
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
    if(ui->backupPath->text().isEmpty() or !QDir(ui->backupPath->text()).exists())
    {
        QMessageBox::critical(this,
                              "Error",
                              "Backup path is not set or invalid path");
        return;
    }

    if(ui->packageList->count() == 0)
    {
        QMessageBox::critical(this,
                              "Error",
                              "Load packages first");
        return;
    }


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


    if(checked == 0)
    {
        QMessageBox::critical(this,
                              "Error",
                              "No packages selected");
        return;
    }

    for(int i=0, c=1; i<ui->packageList->count(); i++)
    {
        QListWidgetItem *item = ui->packageList->item(i);

        if(item->checkState() == Qt::Unchecked)
            continue;

        ui->statusBar->showMessage(QString("Backing up %1 of %2 applications to %3")
                                   .arg(c)
                                   .arg(checked)
                                   .arg(ui->backupPath->text()));

        QString apkPath = adb::apk_path(item->text());
        adb::pull(apkPath, ui->backupPath->text()+"/"+item->text()+".apk");
        c++;
    }

    ui->statusBar->showMessage(QString("Done backing up %1 applications to %2")
                               .arg(checked)
                               .arg(ui->backupPath->text()), 2000);
}

void MainWindow::on_buttonBrowse_clicked()
{
    QString backupDir = QFileDialog::getExistingDirectory(this);
    if(QDir(backupDir).exists())
        ui->backupPath->setText(backupDir);
}
