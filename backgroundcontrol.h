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
    HWND hffplay;
    void createSubDesktop();
    void closeSubDesktop();


    STARTUPINFO si{ 0 };
    PROCESS_INFORMATION pi{ 0 };
    LPCWSTR lpParam;// = L" C:\\Users\\ASUS\\Desktop\\test.mp4 -noborder -x 1920 -y 1080 -loop 0";
    LPCWSTR ffplayer;



private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

private:
    Ui::backgroundcontrol *ui;
};

#endif // BACKGROUNDCONTROL_H
