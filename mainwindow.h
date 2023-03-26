#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//主控制窗口
#include <QMainWindow>
#include "processlist.h"
#include "wininfo.h"

#include "stable.h"
#include <qsystemtrayicon.h>

#include "character.h"
#include "reminder.h"
#include "workclock.h"
#include "backgroundcontrol.h"
#define MaxCharacterNum 20
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
    bool Create_character();

    QString CharacterFolder;
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

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

    void on_textEdit_textChanged();

    void on_pushButton_8_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_checkBox_7_clicked(bool checked);

private:
    Ui::MainWindow *ui;
    processlist* sub1;
    wininfo * sub2;
    backgroundcontrol * sub3;
    workclock* nowclock;
    character * sub_show;//之后这个将成为诸多character的临时索引
    QListWidgetItem *NowItem;
//    int NowItemIndex;
    //    character * mycharacters[MaxCharacterNum];
    int CharacterNum;
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
