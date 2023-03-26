#ifndef WORKCLOCK_H
#define WORKCLOCK_H

#include <QWidget>
#include "stable.h"
namespace Ui {
class workclock;
}
class timeblock
{
public:
    timeblock() {start = 0;end = 1;interval=1;color = QColor(0,0,0);}
    timeblock(float start,float end, QColor color,QString describe = "empty");
    float start;
    float end;
    float interval;
    float startangle;//角度
    float endangle;//角度
    QColor color;
    QString describe;
};
class workclock : public QWidget
{
    Q_OBJECT

public:
    explicit workclock(QWidget *parent = nullptr);
    ~workclock();

    QRectF textRectF(double radius, int pointSize, double angle);
    void init();
    QList<timeblock> timeblocks;
    QList<QColor> colors;
    QTime time;
    void painttimeblocks(QPainter &painter);
    bool mode; //0=12,1=24

    int hour;
    int min;
    int sec;
    \

    QColor hourColor;
    QColor minuteColor;
    QColor secondColor;
    QColor bkColor;
    QRect rect;
    int rectrange;
    int side;
private:
    Ui::workclock *ui;
protected:
    void paintEvent(QPaintEvent* event);

};

#endif // WORKCLOCK_H
