#include "wininfo.h"
#include "ui_wininfo.h"
BOOL CALLBACK EnumChildWindows(HWND hWnd,LPARAM){
    //char WindowTitle[100]={0};
    //QString str;
    //LPWSTR str = "1";
    //Cnum++;
    //::GetWindowText(hWnd,str,100);


    return true;
}

wininfo::wininfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::wininfo)
{
    ui->setupUi(this);

    Cnum = 0;
}

wininfo::~wininfo()
{
    delete ui;
}

void wininfo::on_pushButton_clicked()
{
    showWindows();
}

void wininfo::showWindows(){
    ui->label->setText("1dfsf");

    HWND hd = GetDesktopWindow();
    hd = GetWindow(hd,GW_CHILD);
    LPWSTR s = new wchar_t[11];
    QString str;
    //while(hd != NULL){
    for(int i=0;(i<10)&&(hd != NULL);i++){
        GetWindowText(hd,s,200);
        str = QString::fromWCharArray(s);
        ui->label->setText(str);
        //ui->treeWidget.a
        Cnum++;
        ui->tableWidget->insertRow(Cnum);
        ui->tableWidget->setItem(Cnum,0,new QTableWidgetItem(str));

        hd = GetNextWindow(hd,GW_HWNDNEXT);
    }
    delete []s;
}
