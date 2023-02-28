#include "character.h"
#include "ui_character.h"

character::character(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::character)
{
    ui->setupUi(this);

//    actions[0].setImgDir(characterFolder+"/relax");
//    actions[1].setImgDir(characterFolder+"/move");
//    actions[2].setImgDir(characterFolder+"/interact");
//    actions[3].setImgDir(characterFolder+"/sit");
//    actions[4].setImgDir(characterFolder+"/sleep");
//    actions[5].setImgDir(characterFolder+"/special");

    actions[1].setMovexy(2,0);

    actions[0].StableP += QPoint(0,-1);
    actions[1].StableP += QPoint(0,-3);
//    actions[5].StableP += QPoint(0,-60);

    actions[0].nextaction = &actions[1]; 
    actions[1].nextaction = &actions[0];
    actions[2].nextaction = &actions[0];
    actions[3].nextaction = &actions[0];
    actions[4].nextaction = &actions[0];
    actions[5].nextaction = &actions[0];

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
    setWindowFlag(Qt::Tool);


    mTimer_pos = new QTimer(this);//这里可以优化，加个判断句实现浮空高刷新率，非浮空低刷新。
    mTimer_pos->start(10);
    connect(mTimer_pos,SIGNAL(timeout()),this,SLOT(Automove()));

    soundeffect = new QSoundEffect;
    soundeffect->setVolume(0.25);


    TipCaption = new tipcap(this);//不知道为什么这个this没用
    sub_ask = new AskAnswer(this);
    mReminder = new reminder;
}

character::~character()
{
    delete mReminder;
    delete TipCaption;
    delete sub_ask;
    delete mTimer_pos;
    delete ui;
}
void character::UpdateFolder(QString nowfolder){
    characterFolder = nowfolder;
    actions[0].setImgDir(characterFolder+"/relax");
    actions[1].setImgDir(characterFolder+"/move");
    actions[2].setImgDir(characterFolder+"/interact");
    actions[3].setImgDir(characterFolder+"/sit");
    actions[4].setImgDir(characterFolder+"/sleep");
    actions[5].setImgDir(characterFolder+"/special");
    soundeffect->setSource(QUrl::fromLocalFile(characterFolder+"/sound/click.wav"));
    TipCaption->UpdateFolder(characterFolder+"/sound");
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
            if(tPos.rx()>10){
                sub_ask->show();
            }
            if(tPos.rx()<10){
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
//            TipCaption->setCaptionVoice(nowaction->Show_LUp+pos());
            TipCaption->setCaptionVoice(nowaction->Show_LUp+QPoint(13,-10));
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
            if(nowaction==&actions[0]){
                if(rand()%2==1){
                    IfRLTurn = !IfRLTurn;
                }
                if(rand()%10==0){
                    nowaction->reset(true);
                    actions[5].Ifloop = 1;//特殊动作只能重复一次
                    setAction(&actions[5]);//special
                }
                else{
                    nowaction->reset(true);
                    setAction(&actions[1]);
                }
            }
            else{
                if(nowaction==&actions[2]){
                    nowaction->reset();
                }
                else{
                    nowaction->reset(true);
                }

                setAction(&actions[0]);
            }
        }
    }
    nowaction->Paint(p,StableP,NowScale,IfRLTurn);
}
