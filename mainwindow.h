#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QMessageBox>
#include <QDebug>
#include <QProgressDialog>
#include <QFileDialog>
#include "adb.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

private slots:
    void monitorDevice();
    void on_btnLoad_clicked();
    void on_btnMarkAll_clicked();
    void on_btnUnmarkAll_clicked();
    void on_btnBackup_clicked();
    void on_buttonBrowse_clicked();

private:
    Ui::MainWindow *ui;
    QTimer timerDeviceMonitor;
};

#endif // MAINWINDOW_H
