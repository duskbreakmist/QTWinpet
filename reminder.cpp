#include "reminder.h"
#include "ui_reminder.h"

reminder::reminder(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::reminder)
{
    ui->setupUi(this);
    setWindowTitle("计时器");
    datetime = new QDateTime;
    UpdateTime();
    mTimer = new QTimer(this);
    mTimer->start(300);
    connect(mTimer,SIGNAL(timeout()),this,SLOT(UpdateTime()));

    ui->horizontalSlider->setRange(0,100);

    ifpause = false;
    ifstart = false;

    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit->setReadOnly(true);
    ui->dateEdit->setFocusPolicy(Qt::NoFocus);
}

reminder::~reminder()
{
    delete datetime;
    delete ui;
}
const QTime reminder::timeAdd(QTime& t1,QTime& t2){
    return t1.addSecs(3600* t2.hour()+60*t2.minute()+t2.second());
}
const QTime reminder::timeSub(QTime& t1,QTime& t2){
    return t1.addSecs(-(3600* t2.hour()+60*t2.minute()+t2.second()));
}

int reminder::sumTimeSec(const QTime t){
    return 3600* t.hour()+60*t.minute()+t.second();
}

void reminder::UpdateTime(){

    if(!ifstart){
        //未开始
        ui->timeEdit->setTime(datetime->currentDateTime().time());
        startTime = ui->timeEdit->time();
        ui->timeEdit_3->setTime(timeAdd(startTime,lessTime));
    }
    else {
        if(lessTime.hour()+lessTime.minute()+lessTime.second()==0){
            //时间结束
            qDebug()<<"TImeout!";
            ifstart = false;
            ui->pushButton->setDisabled(false);
            emit reminder_timeout(ui->timeEdit_4->time());

        }
        else{
            if(!ifpause){
                //暂停了
                if(ui->dateEdit->time().second()!= datetime->currentDateTime().time().second()){

                    ui->timeEdit_2->setTime(lessTime.addSecs(-1));
                    lessTime = ui->timeEdit_2->time();

                }
            }
            pecent =(100*sumTimeSec(ui->timeEdit_2->time()))/sumTimeSec(ui->timeEdit_4->time());
            ui->label_7->setText(QString::number(pecent));
            ui->horizontalSlider->setValue(pecent);
        }
    }

    //时间显示
    ui->dateEdit->setDateTime(QDateTime::currentDateTime());

}

void reminder::on_pushButton_clicked()
{
    //开始
    ifstart = true;
    ui->pushButton->setDisabled(true);
    ui->timeEdit_4->setTime(ui->timeEdit_2->time());
    qDebug()<<ui->timeEdit_2->time();
}


void reminder::on_pushButton_2_clicked()
{
   //暂停
    ifpause = !ifpause;
    if(ifpause){
        ui->pushButton_2->setText("继续");
    }
    else{
        ui->pushButton_2->setText("暂停");
    }


}


void reminder::on_pushButton_3_clicked()
{
    //结束复位
    ifstart = false;
//    ui->timeEdit->setFocusPolicy(Qt::ClickFocus);
//    ui->timeEdit_2->setFocusPolicy(Qt::ClickFocus);
//    ui->timeEdit_3->setFocusPolicy(Qt::ClickFocus);

    ui->pushButton->setDisabled(false);
}


void reminder::on_timeEdit_2_userTimeChanged(const QTime &time)
{
    if(!ifstart){
        startTime = ui->timeEdit->time();
        lessTime = ui->timeEdit_2->time();
        endTime = timeAdd(startTime,lessTime);
        ui->timeEdit_3->setTime(endTime);
        ui->timeEdit_3->update();
//        qDebug()<<"changed";
    }
    else{

    }

}


void reminder::on_timeEdit_userTimeChanged(const QTime &time)
{

}


void reminder::on_horizontalSlider_valueChanged(int value)
{

}

