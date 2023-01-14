#include "askanswer.h"
#include "ui_askanswer.h"

AskAnswer::AskAnswer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AskAnswer)
{
    ui->setupUi(this);
//    setWindowFlag(Qt::FramelessWindowHint);
    setWindowFlag(Qt::Tool);

    SaveFloder ="./Data";
    IfExtend = false;

    thisWinId = (HWND)winId();
}

AskAnswer::~AskAnswer()
{
    delete ui;
}
void AskAnswer::change_transparent(int i){
    //setWindowOpacity(i/100.0);
}
void AskAnswer::on_pushButton_4_clicked()
{
    SaveTxt();
}
bool AskAnswer::CreateFolder(){
    QDir * folder = new QDir;
    bool exist = folder->exists(SaveFloder);
    if(!exist){
        bool ok = folder->mkdir(SaveFloder);
        if(ok){
            qDebug()<<"create success";
        }
        else{
            qDebug()<<"create error";
        }
    }
    else{
        qDebug()<<"exist";
    }
    delete folder;
    return true;
}
bool AskAnswer::SaveTxt(){
    CreateFolder();
    QString filename = SaveFloder +"/note.txt";
    QString textEdit_txt = ui->textEdit_2->toPlainText();
    if(textEdit_txt.isEmpty()){
        qDebug()<<"txt empty";
    }
    else{
        QFile f(filename);
        QDateTime date_now = QDateTime::currentDateTime(); //获取系统现在的时间
        QString str_now = date_now.toString("yyyy-MM-dd-hh-mm-ss");

        textEdit_txt.append(','+str_now+"\n");
        QByteArray log = textEdit_txt.toLocal8Bit();
        if(!f.open(QIODevice::Append)){
            qDebug()<<"f open error,文件不存在";
            f.open(QIODevice::WriteOnly);
            f.write(log,log.length());
            f.close();
        }
        else{
            qDebug()<<"add success";
            f.write(log,log.length());
            f.close();
        }
    }
    return true;
}
bool AskAnswer::SaveInteraction(){
    CreateFolder();
    QString filename = SaveFloder +"/interactionlog.txt";
    QString textEdit_txt = ui->textEdit_2->toPlainText();
    if(textEdit_txt.isEmpty()){
        qDebug()<<"txt empty";
    }
    else{
        QFile f(filename);
        QDateTime date_now = QDateTime::currentDateTime(); //获取系统现在的时间
        QString str_now = date_now.toString("yyyy-MM-dd-hh-mm-ss");

        textEdit_txt.append(','+str_now+"\n");
        QByteArray log = textEdit_txt.toLocal8Bit();
        if(!f.open(QIODevice::Append)){
            qDebug()<<"f open error";
            f.open(QIODevice::WriteOnly);
            f.write(log,log.length());
            f.close();
        }
        else{
            f.write(log,log.length());
            f.close();
        }
    }

    return true;
}
bool AskAnswer::UpdateNowWords(){
    NowWords = "你是否清醒";
    ui->textEdit->setText(NowWords);
    return true;
}
void AskAnswer::on_pushButton_5_clicked()
{
    //展开
    IfExtend = !IfExtend;
    if(IfExtend){
        ui->pushButton_5->setText("收起");
        resize(250,250);
    }
    else{
        ui->pushButton_5->setText("展开");
        resize(250,115);
    }
}


void AskAnswer::on_pushButton_6_clicked()
{
    //历史记录
}

