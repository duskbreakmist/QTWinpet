#include "tipcap.h"
#include "ui_tipcap.h"

tipcap::tipcap(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tipcap)
{
    ui->setupUi(this);
    setWindowFlag(Qt::Tool);
//    VoiceFolder = "/sound";
//    CaptionFile = "./Data/CaptionFile.txt";

    mytimer = new QTimer(this);
    mytimer->setInterval(1000);
    connect(mytimer,SIGNAL(timeout()),this,SLOT(WindowHide()));

    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlag(Qt::FramelessWindowHint);

    ui->textEdit->setStyleSheet("background-color: rgba(15, 55, 215, 100);");

}

tipcap::~tipcap()
{
    delete ui;
}
void tipcap::UpdateFolder(QString nowfolder){
    VoiceFolder = nowfolder;
    CaptionFile = nowfolder+"/CaptionFile.txt";
    readCaption();
}
bool tipcap::setCaptionVoice(QPoint LUpoint){
    //this->move()
    LUpoint += QPoint(-50,-60);
    move(LUpoint);
    show();

    int temp = rand()%CaptionNum;
    ui->textEdit->setText(Captions.at(temp));
    ui->textEdit->setAlignment(Qt::AlignCenter);
    mytimer->start(VoiceTime.at(temp).toInt());

    return true;
}
void tipcap::WindowHide(){
    hide();
    mytimer->stop();
}
bool tipcap::readCaption(){
    QFile f(CaptionFile);
    if(!f.open(QIODevice::ReadOnly)){
        qDebug()<<"f open error,文件不存在";
        f.close();
        return false;
    }

    qDebug()<<"read success";
    QTextStream * read = new QTextStream(&f);
    QStringList Data = read->readAll().split("\n");
    qDebug()<<Data.count();
    VoiceTime.clear();
    Captions.clear();
    for(int i=0;i<Data.count();++i)
    {
        QStringList strLine = Data.at(i).split(",");     //一行中的单元格以，区分
        qDebug()<<strLine.at(0);                        //打印出每行的第一个单元格的数据
        VoiceTime.append(strLine.at(0));
        Captions.append(strLine.at(1));
    }

    CaptionNum = Captions.length();
    qDebug()<<Captions.length()<<"+"<<VoiceTime.length();
    f.close();
    return true;
}
