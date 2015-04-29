#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QDebug>
#include <QProgressDialog>

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
    bool adb_pull(QString remotePath, QString localPath);
    QString adb_apk_path(QString packageName);

private slots:
    void on_btnLoad_clicked();

    void on_btnMarkAll_clicked();

    void on_btnUnmarkAll_clicked();

    void on_btnBackup_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
