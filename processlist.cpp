#include "processlist.h"
#include "ui_processlist.h"

processlist::processlist(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::processlist)
{
    ui->setupUi(this);
    ui->tableWidget1->setColumnWidth(0,140);
    ui->tableWidget1->setColumnWidth(1,50);
    ui->tableWidget1->setColumnWidth(2,50);
    ui->tableWidget1->setColumnWidth(3,50);
    ui->tableWidget1->setColumnWidth(4,80);
    showProcess();
    //----
    mTimer = new QTimer(0);
    IfUpdate = true;
    mTimer->setInterval(500);
    connect(mTimer,SIGNAL(timeout()),this,SLOT(Update()));
    mTimer->stop();
}

processlist::~processlist()
{
    delete ui;
}
void processlist::Update(){
    if(IfUpdate){
        showProcess();
    }
    else{

    }
}
void processlist::showProcess()
{
    PROCESS_MEMORY_COUNTERS nMen;

    HANDLE hsnpShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
    HANDLE nHandle;
    if(hsnpShot == INVALID_HANDLE_VALUE){
        ui->label->setText("error");
        return;
    }
    ui->label->setText("start");
    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);
    BOOL bFlag = Process32First(hsnpShot,&pe);
    QString str;
    int i=0;
    //for(int row=ui->tableWidget1->rowCount();row>=0;row--){
      //  ui->tableWidget1->removeRow(i);
    //}
    ui->tableWidget1->setRowCount(0);
    while(bFlag){
        ui->tableWidget1->insertRow(i);
        str = QString::fromWCharArray(pe.szExeFile);
        ui->tableWidget1->setItem(i,0,new QTableWidgetItem(str));
        str = QString::number(pe.th32ProcessID);
        ui->tableWidget1->setItem(i,1,new QTableWidgetItem(str));
        str = QString::number(pe.cntThreads);
        ui->tableWidget1->setItem(i,2,new QTableWidgetItem(str));
        str = QString::number(pe.th32ParentProcessID);
        ui->tableWidget1->setItem(i,3,new QTableWidgetItem(str));

        nHandle = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pe.th32ProcessID);
        GetProcessMemoryInfo(nHandle,&nMen,sizeof(PROCESS_MEMORY_COUNTERS));
        str = QString::number(nMen.WorkingSetSize/1024);
        ui->tableWidget1->setItem(i,4,new QTableWidgetItem(str));//内存占用
        //GetProcessFilePath(nHandle, str);


        bFlag = Process32Next(hsnpShot,&pe);
        i++;

        ui->label->setText(QString::number(i));
    }
    //ui->label->setText("end");


}

void processlist::on_pushButton_update_clicked()
{

   IfUpdate=true;
   ui->label_7->setText("自动更新已开");
   mTimer->start();
}


void processlist::on_pushButton2_clicked()
{
    IfUpdate=false;
    ui->label_7->setText("自动更新已关");
    mTimer->stop();
}

