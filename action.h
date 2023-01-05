#ifndef ACTION_H
#define ACTION_H
#include "qimage.h"
#include "qsize.h"
#include <QObject>
#include <qdir.h>
#include <QDebug>
#include <qpainter.h>
class action
{
public:
    action(QString dir= "");
    int id;

    int state;
    //1 = work
    //0 = empty
    QString name;
    QString ImgDir;
    QStringList ImgList;
    QSize ImgSize;
    QSize ShowSize;
    QImage NowImg;
    int ImgNum;
    int nowIndex;
    bool Ifloop;
    int LoopStartIndex;
    int LoopEndIndex;
    bool Ifend;
    bool IfChangeSize;//节约资源
    action* nextaction;
    bool setImgDir(QString dir);
    bool setMovexy(int x,int y);

    bool setNext(action* next);

    action* returnNext();
    void reset(){Ifend = false;nowIndex=0;}
    //图像显示和移动部分
    bool Paint(QPainter& p);
    int MoveMode;
    int Movex;
    int Movey;
    //0 = 静止
    //1 = 正向;-1 反向
    QPoint MoveWidget(QPoint nowp);
};

#endif // ACTION_H
