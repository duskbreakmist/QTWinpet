#include "action.h"


action::action(QString dir)
{

    id = 0;
    name = "";
    state = 0;
    ImgDir = "";
    ImgNum = 0;
    nowIndex = 0;

//    Ifloop = true;
    Ifloop = 1;//只一次

    Ifend = false;

    IfChangeSize = false;
    MoveMode = 0;
    Movexy = QPoint(0,0);


    setImgDir(dir);
}
bool action::setMovexy(int x,int y){
    Movexy.setX(x);
    Movexy.setY(y);
    return true;
}
bool action::setImgDir(QString dir){
    if(dir == ImgDir){
        qDebug()<<"图片路径相同";
        return false;
    }
    else{
        QDir tmpDir(dir);
        QFileInfoList listInfo
                = tmpDir.entryInfoList
                (QDir::Files|QDir::Dirs|QDir::NoDotAndDotDot,QDir::Name);
        if(listInfo.isEmpty()){
            ImgNum = 0;
            qDebug()<<"图片文件夹为空或无法读取";
            return false;
        }
        if(true){//应该有个判断是否是图片文件
            qDebug()<<"图片文件夹更新";
            state = 1;
            ImgDir = dir;
            ImgList.clear();
            foreach (QFileInfo strFileInfo, listInfo) {
                ImgList.append(strFileInfo.filePath());
            }
            ImgNum = ImgList.size();
            ImgSize = QImage(ImgList.first()).size();
            StableP = QPoint(ImgSize.rwidth()/2,ImgSize.rheight());
        }
        return true;
    }
}
bool action::Paint(QPainter& p,QPoint ScreenStable,double Scale,bool IfRLturn){

    ShowSize = Scale* ImgSize;
    Show_LUp =ScreenStable-StableP*Scale;

    if(nowIndex<ImgNum){

        if(IfChangeSize&&false){
            NowImg = QImage(ImgList[nowIndex]).scaled(ShowSize);
            p.drawImage(QPointF(0,0),NowImg);
        }
        else{
            //p.drawRect(QRectF(Show_LUp,ShowSize));
            if(IfRLturn){
                //p.drawRect(QRectF(Show_LUp,ShowSize));
                //p.drawImage(,)
                p.drawImage(QRectF(Show_LUp,ShowSize),
                            QImage(ImgList[nowIndex]).mirrored(true,false)
                            );
            }
            else{
                //p.drawRect(QRectF(Show_LUp,ShowSize));
                //p.drawImage(,)
                p.drawImage(QRectF(Show_LUp,ShowSize),
                            QImage(ImgList[nowIndex])
                            );
            }
        }
        nowIndex++;
    }
    if(nowIndex>=ImgNum){
        Ifloop --;
        Ifend = true;
        if(Ifloop!=0){
            if(Ifloop<0){
                Ifloop = -1;
                nowIndex = 0;
                Ifend = false;
            }
            else{

                nowIndex = 0;
                Ifend = false;
            }
        }

    }
    return true;
}
QPoint action::MoveWidget(QPoint nowp,bool IfRLTurn){
    if(IfRLTurn){
        nowp.setX(nowp.x()-Movexy.x());
        nowp.setY(nowp.y()+Movexy.y());
    }else{
        nowp += Movexy;
    }
    if(nowp.x()>1410){
        nowp.setX(-90);
    }
    if(nowp.x()<-90){
        nowp.setX(1410);
    }
    if(nowp.y()>1080){
        nowp.setY(0);
    }
    return nowp;
}
bool action::setNext(action* next){
    if(next==NULL){
        return false;
    }
    return true;
    nextaction = next;
}
action* action::returnNext(){
    reset(true);//返回下一个后就复位
    return nextaction;
}
void action::reset(bool IfRandom){
    if(IfRandom){
        Ifloop = rand()%3+1; //1~3
    }
    else{
        Ifloop = 1;//只一次
    }
    Ifend = false;
    nowIndex=0;
}
