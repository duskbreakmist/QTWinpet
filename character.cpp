#include "character.h"
#include "ui_character.h"

character::character(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::character)
{
    ui->setupUi(this);

    QMovie *movie = new QMovie(":/new/prefix1/gif/sakana1.gif");
    movie->setScaledSize(QSize(400,200));
    ui->label->setMovie(movie);
    movie->start();

    thisWinId = (HWND)winId();
    setAttribute(Qt::WA_TranslucentBackground);
    //setAttribute(Qt::WA_TransparentForMouseEvents, true);
    setWindowFlag(Qt::FramelessWindowHint);
    //SetWindowPos(thisWinId,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
    SetWindowLong(thisWinId,
                  GWL_EXSTYLE,
                  GetWindowLong(
                      thisWinId, GWL_EXSTYLE)
                  |WS_EX_TRANSPARENT | WS_EX_LAYERED);
}

character::~character()
{
    delete ui;
}
void character::change_transparent(int i){
    setWindowOpacity(i/100.0);
}
void character::change_state(int i){
    switch (i) {
    case 0:


        setWindowFlag(Qt::Window);
        qDebug()<<"set0trans";
        break;
    case 1:
        qDebug()<<"set1trans";

        setWindowFlag(Qt::Window);
        break;
    //----
    default:
        break;
    }

}
void character::Automove(){
    QPoint nPos = pos();
    if(nPos.x()<2000){
        nPos.setX(nPos.x()+100);
    }
    else{
        nPos.setX(nPos.x()-100);
    }

    move(nPos);
}
void character::mouseMoveEvent(QMouseEvent* event){
    if(mouse_clicked_flag){
        QPoint tPos = event->globalPosition().toPoint()-screenPos;
        move(pos()+tPos);
        screenPos = event->globalPosition().toPoint();
    }
    //QWidget::moveMoveEvent(event);
}
void character::mousePressEvent(QMouseEvent* event){
    mouse_clicked_flag = true;
    screenPos = event->globalPosition().toPoint();
}
void character::mouseReleaseEvent(QMouseEvent* event){
    mouse_clicked_flag = false;
}

