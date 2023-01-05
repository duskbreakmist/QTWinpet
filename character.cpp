#include "character.h"
#include "ui_character.h"

character::character(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::character)
{
    ui->setupUi(this);

    //action act_interact("E:/File/BlenderWorkPlace/blender3.4/ailini_all/outpng2");
    action act_interact("E:/File/SpineWorkPlace/outputPNG/白面鸮/interact");
    action act_Rwalk("E:/File/SpineWorkPlace/outputPNG/白面鸮/MoveR");
    action act_relax("E:/File/SpineWorkPlace/outputPNG/白面鸮/relax");
    action act_sleep("E:/File/SpineWorkPlace/outputPNG/白面鸮/sleep");
    //上面都是临时变量，需要下面去储存。
    actions[0] = act_relax;
    actions[1] = act_Rwalk;
    actions[2] = act_interact;
    actions[3] = act_sleep;

    actions[1].nextaction = &actions[0];
    actions[1].Ifloop = false;
    actions[1].setMovexy(2,0);
    actions[0].nextaction = &actions[1];
    actions[0].Ifloop = false;
    actions[2].Ifloop = false;
    actions[2].nextaction = &actions[0];
    setAction(&actions[1]);

    this->resize(nowaction->ImgSize);

    thisWinId = (HWND)winId();
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlag(Qt::FramelessWindowHint);

    show();

    mTimer = new QTimer(this);
    mTimer->start(40);
    connect(mTimer,SIGNAL(timeout()),this,SLOT(Automove()));
}

character::~character()
{
    delete ui;
}
void character::setAction(action* act){ 
    AutoRisize(NowScale*act->ImgSize);
    nowaction = act;
}
void character::AutoRisize(QSize NewSize){
    resize(NewSize);
    move(
                pos().rx()+(NowSize.rwidth() - NewSize.rwidth())/2,
                pos().ry()+NowSize.rheight() - NewSize.rheight());
    NowSize = NewSize;
}
void character::change_transparent(int i){
    setWindowOpacity(i/100.0);
}
void character::change_size(int i){
    NowScale = i/100.0;
    AutoRisize(NowScale*nowaction->ImgSize);
    //resize(NowSize);
}
void character::change_state(int i){
    switch (i) {
    case 0:
        setWindowFlag(Qt::X11BypassWindowManagerHint);
        qDebug()<<"set0trans";
        break;
    case 1:
        qDebug()<<"set1trans";
        break;
    //----
    default:
        break;
    }

}
void character::Automove(){

    update();//更新图片序列
    move(nowaction->MoveWidget(pos()));//更新窗口位置。

}

void character::mouseMoveEvent(QMouseEvent* event){
    if(mouse_clicked_flag){
        QPoint tPos = event->globalPosition().toPoint()-screenPos;
        move(pos()+tPos);
        screenPos = event->globalPosition().toPoint();
    }

}
void character::mousePressEvent(QMouseEvent* event){
    mouse_clicked_flag = true;
    screenPos = event->globalPosition().toPoint();

    nowaction->returnNext();
    setAction(&actions[2]);
}
void character::mouseReleaseEvent(QMouseEvent* event){
    Q_UNUSED(event);
    mouse_clicked_flag = false;
}
void character::paintEvent(QPaintEvent* event){
    Q_UNUSED(event);
    QPainter p(this);
    p.scale(NowScale,NowScale);
    nowaction->Paint(p);
    if(nowaction->Ifend){
        setAction(nowaction->returnNext());
    }
}
