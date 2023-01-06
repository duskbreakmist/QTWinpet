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

    actions[0].StableP.setY(actions[0].StableP.y()-1);
    actions[1].StableP.setY(actions[1].StableP.y()-3);
    actions[3].StableP.setY(actions[3].StableP.y()-6);
    actions[1].nextaction = &actions[0];
    actions[1].Ifloop = false;
    actions[1].setMovexy(2,0);
    actions[0].nextaction = &actions[1];
    actions[0].Ifloop = false;
    actions[2].Ifloop = false;
    actions[2].nextaction = &actions[0];


    setAction(&actions[1]);
    IfRLTurn = true;

    resize(SCREENwidth,SCREENheight);//不再改变
    StableP = QPoint(SCREENwidth/2,SCREENheight);
    thisWinId = (HWND)winId();
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlag(Qt::FramelessWindowHint);

    show();

    mTimer = new QTimer(this);
    mTimer->start(40);
    connect(mTimer,SIGNAL(timeout()),this,SLOT(Automove()));

    soundeffect = new QSoundEffect;
    soundeffect->setVolume(0.5);
    soundeffect->setSource(QUrl::fromLocalFile("E:/File/C++File/QT/taskmanager/sound/click.wav"));
    //player->setSource();

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
    move(nowaction->MoveWidget(pos(),IfRLTurn));//更新窗口位置。

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
    if(event->button()==Qt::RightButton){
        nowaction->returnNext();
        setAction(&actions[2]);
        soundeffect->play();
    }

}
void character::mouseReleaseEvent(QMouseEvent* event){
    Q_UNUSED(event);
    mouse_clicked_flag = false;
}
void character::paintEvent(QPaintEvent* event){
    Q_UNUSED(event);
    QPainter p(this);

    nowaction->Paint(p,StableP,NowScale,IfRLTurn);
    if(nowaction->Ifend){
        if(rand()/(RAND_MAX*1.0)>0.5){
            IfRLTurn = !IfRLTurn;
        }
        setAction(nowaction->returnNext());
    }
}
