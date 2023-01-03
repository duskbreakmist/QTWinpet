#ifndef WININFO_H
#define WININFO_H

#include <QWidget>
#include "stable.h"
namespace Ui {
class wininfo;
}

class wininfo : public QWidget
{
    Q_OBJECT

public:
    explicit wininfo(QWidget *parent = nullptr);
    ~wininfo();
    void showWindows();
private slots:
    void on_pushButton_clicked();

private:
    Ui::wininfo *ui;

    int Pnum;
    int Cnum;

};

#endif // WININFO_H
