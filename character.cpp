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
    //actions[3] = act_sleep;

    actions[0].StableP.setY(actions[0].StableP.y()-1);
    actions[1].StableP.setY(actions[1].StableP.y()-3);
    //actions[3].StableP.setY(actions[3].StableP.y()-6);
    actions[1].nextaction = &actions[0];
    actions[1].setMovexy(2,0);
    actions[0].nextaction = &actions[1]; 
    actions[2].nextaction = &actions[0];

    setAction(&actions[1]);

    IfRLTurn = true;
    IfFloat = true;
    mouse_clicked_L = false;
    mouse_clicked_R = false;
    IfPhy = true;
    m_g = QPointF(0,0.5);
    ground_y = 574;
    ActionMode = 1;

    resize(SCREENwidth,SCREENheight);//不再改变
    StableP = QPoint(SCREENwidth/2,SCREENheight);
    thisWinId = (HWND)winId();
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlag(Qt::FramelessWindowHint);

    show();

    mTimer_pos = new QTimer(this);//这里可以优化，加个判断句实现浮空高刷新率，非浮空低刷新。
    mTimer_pos->start(10);
    connect(mTimer_pos,SIGNAL(timeout()),this,SLOT(Automove()));

    soundeffect = new QSoundEffect;
    soundeffect->setVolume(0.25);
    soundeffect->setSource(QUrl::fromLocalFile("E:/File/C++File/QT/taskmanager/sound/click.wav"));

    TipCaption = new tipcap;
    sub_ask = new AskAnswer;
}

character::~character()
{
    delete ui;
}
void character::setAction(action* act){ 
    AutoRisize(NowScale*act->ImgSize);
    nowaction = act;
}
void character::setActionMode(int i){
    ActionMode = i;
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
//void character::AutoPicUpdate(){
//    update();//更新图片序列
//}
bool character::Automove(){
    loopval++;
    if((loopval%4)==0){//4分频
        update();
    }
    else{
        if(!IfFloat){
            return false;
        }
    }
    if(IfPhy){
        if(IfFloat){
            m_p += m_v/2;
            m_v += m_g;
            if(m_p.y()>= ground_y){
                m_p.setY(ground_y);
                if(m_v.manhattanLength()<4){
                    m_v = QPoint(0,0);
                    IfFloat = false;
                }
                m_v /=-2;
            }

            move(m_p.toPoint());
        }
        else{
            move(nowaction->MoveWidget(pos(),IfRLTurn));//更新窗口位置。
        }
    }
    else{
        move(nowaction->MoveWidget(pos(),IfRLTurn));//更新窗口位置。
    }
    return true;
}
void character::reset(){
    move(0,574);
    m_v = QPoint(0,0);
}
void character::mouseMoveEvent(QMouseEvent* event){
    if(mouse_clicked_L){
        QPoint tPos = event->globalPosition().toPoint()-screenPos;
        move(pos()+tPos);
        screenPos = event->globalPosition().toPoint();
        m_v = tPos;
        mouse_moved_L = true;
        //if(m_v.manhattanLength()>10){m_v *= 10/m_v.manhattanLength();}
    }
    if(mouse_clicked_R){
        mouse_moved_R = true;
        QPoint tPos = event->globalPosition().toPoint()-screenPos;
//        qDebug()<<tPos
//        if(tPos.x()>0){
//            sub_ask->show();
//        }
    }

}
void character::mousePressEvent(QMouseEvent* event){
    //下面防止按下后还会动
    if(nowaction!= &actions[0]){
        nowaction->reset();//保存动作不变
        nowaction = &actions[0];//始终是静止状态
    }

    //mouse_clicked_flag = true;

    if(event->button()==Qt::RightButton){

        screenPos = event->globalPosition().toPoint();
        mouse_clicked_R = true;
        mouse_moved_R = false;
    }
    //保证左右键不同时按下
    else if(event->button()==Qt::LeftButton){
        mouse_clicked_L = true;
        IfFloat = false;
        screenPos = event->globalPosition().toPoint();
        mouse_moved_L = false;
    }

}
void character::mouseReleaseEvent(QMouseEvent* event){
    //Q_UNUSED(event);

    //mouse_clicked_flag = false;
    if(event->button()==Qt::RightButton){
        mouse_clicked_R = false;

        if(!mouse_moved_R){
            nowaction->reset();
            setAction(&actions[2]);
            soundeffect->play();
        }
        else{
            QPoint tPos = event->globalPosition().toPoint()-screenPos;
            if(tPos.rx()>0){
                sub_ask->show();
            }
        }
    }
    if(event->button()==Qt::LeftButton){
        mouse_clicked_L = false;
        if(mouse_moved_L){
            m_p = pos();
            IfFloat = true;
        }
        else{
            TipCaption->setCaptionVoice(nowaction->Show_LUp+pos());
//            TipCaption->setCaptionVoice(QPoint(1000,100));
            qDebug()<<"怎么了";
        }
    }
    //if()判断是否浮空
}

void character::paintEvent(QPaintEvent* event){
    Q_UNUSED(event);
    QPainter p(this);


    if(nowaction->Ifend){
        if((ActionMode==0)||IfFloat||mouse_clicked_L||mouse_clicked_R){
            nowaction->reset();//保存动作不变
            nowaction = &actions[0];//始终是静止状态
        }
        else{
            if((rand()/(RAND_MAX*1.0)>0.5)&&(nowaction==&actions[0])){
                IfRLTurn = !IfRLTurn;
            }
            setAction(nowaction->returnNext());
        }
    }
    nowaction->Paint(p,StableP,NowScale,IfRLTurn);
}
