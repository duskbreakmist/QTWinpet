#include "character.h"
#include "ui_character.h"

character::character(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::character)
{
    ui->setupUi(this);

    action act_interact("E:/File/BlenderWorkPlace/blender3.4/ailini_all/outpng2");
    action act_walk("E:/File/BlenderWorkPlace/blender3.4/ailini_all/outpng2");
    actions[0] = act_interact;
    actions[1] = act_walk;
    setAction(&actions[0]);


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

    this->resize(act->ImgSize);
    nowaction = act;
}
void character::change_transparent(int i){
    setWindowOpacity(i/100.0);
}
void character::change_size(int i){
    NowScale = i/100.0;
    NowSize = NowScale*nowaction->ImgSize;
    resize(NowSize);
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
}
