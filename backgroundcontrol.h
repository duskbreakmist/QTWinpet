#ifndef BACKGROUNDCONTROL_H
#define BACKGROUNDCONTROL_H

#include <QWidget>
#include "stable.h"
namespace Ui {
class backgroundcontrol;
}

class backgroundcontrol : public QWidget
{
    Q_OBJECT

public:
    explicit backgroundcontrol(QWidget *parent = nullptr);
    ~backgroundcontrol();
    bool ifloop;
    bool ifkeep;    //关闭程序依然保留
    bool ifmusic;
    bool ifautoset;//开机自动设置
    bool ifpaused;

    HWND hffplay;
    bool sendMessage(int key);

    void createSubDesktop();
    void closeSubDesktop(bool t = true);

    void setstaticbk();
    void returnstaticbk();

    bool readinitfile();
    QString initfile;
    STARTUPINFO si{ 0 };
    PROCESS_INFORMATION pi{ 0 };
    LPCWSTR lpParam;// = L" C:\\Users\\ASUS\\Desktop\\test.mp4 -noborder -x 1920 -y 1080 -loop 0";
    LPCWSTR ffplayer;
    QString staticurl;
    PVOID temp2;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_checkBox_2_clicked(bool checked);

    void on_checkBox_3_clicked(bool checked);

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_checkBox_4_clicked(bool checked);

    void on_pushButton_9_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

private:
    Ui::backgroundcontrol *ui;
};

#endif // BACKGROUNDCONTROL_H
