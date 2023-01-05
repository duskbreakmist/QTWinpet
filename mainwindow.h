#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "processlist.h"
#include "wininfo.h"
#include "character.h"
#include "stable.h"
#include <qsystemtrayicon.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Create_TrayIcon();

private slots:

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();
    void on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);
    void on_ShowMainAction();
    void on_ExitAction();
    void TrayIconFlash();

    void on_pushButton_3_clicked();

    void on_checkBox_4_stateChanged(int arg1);

    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_3_stateChanged(int arg1);

    void on_horizontalSlider_valueChanged(int value);

    void on_checkBox_5_stateChanged(int arg1);

    void on_pushButton_5_clicked();

    void on_checkBox_6_stateChanged(int arg1);

    void on_horizontalSlider_2_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    processlist* sub1;
    wininfo * sub2;
    character * sub_show;
    //--
    QIcon icon;
    QIcon icon2;
    QSystemTrayIcon* mSysTrayIcon;
    QMenu*mMenu;
    QAction *mShowMainAction;
    QAction *mExitAction;
    QTimer *mTimer;

    bool Iconflash;
    bool IfFlash;
};
#endif // MAINWINDOW_H