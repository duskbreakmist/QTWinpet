#ifndef ACTION_H
#define ACTION_H
//角色运动行为类
#include "qimage.h"
#include <QObject>
#include "stable.h"
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
//    bool Ifloop;
    int Ifloop;
    //-1==loop,0=noloop,+num=loopnum
    int LoopStartIndex;
    int LoopEndIndex;
    bool Ifend;
    bool IfChangeSize;//节约资源
    action* nextaction;
    bool setImgDir(QString dir);
    bool setMovexy(int x,int y);

    bool setNext(action* next);

    action* returnNext();
    void reset(bool IfRandom=false);
    //图像显示和移动部分
    bool Paint(QPainter& p,QPoint ScreenStable,double Scale=1,bool IfRLturn=false);
    int MoveMode;
    QPoint Movexy;

    QPoint StableP;//想要让图片上的哪个点保持全局不变
    //0 = 静止
    //1 = 正向;-1 反向
    QPoint Show_LUp;//左上角
    QPoint MoveWidget(QPoint nowp,bool IfRLTurn=false);
};

#endif // ACTION_H
