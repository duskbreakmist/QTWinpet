#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    sub1 = new processlist;
    sub2 = new wininfo;
    sub_show = new character;
    sub_show->setWindowFlag(Qt::Tool);
    ui->stackedWidget->addWidget(sub1);
    ui->stackedWidget->addWidget(sub2);
    ui->stackedWidget->setCurrentWidget(sub1);
    ui->stackedWidget->setCurrentIndex(0);
    sub_show->show();
    //------
    Create_TrayIcon();
    //-----
    ui->horizontalSlider->setRange(0,100);
    ui->horizontalSlider->setValue(79);

    ui->horizontalSlider_2->setRange(10,100);
    ui->horizontalSlider_2->setValue(58);
    ui->checkBox_3->setChecked(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::Create_TrayIcon(){
    mSysTrayIcon = new QSystemTrayIcon(this);

    icon = QIcon(":/new/prefix1/picture/boji.png");
    icon2 = QIcon(":/new/prefix1/picture/hongxia.png");
    setWindowIcon(icon);//
    mSysTrayIcon->setIcon(icon);
    mSysTrayIcon->setToolTip("hellomyf");
    connect(mSysTrayIcon,
            SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this,
            SLOT(on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason))
            );


    mShowMainAction = new QAction("显示主界面",this);
    mExitAction = new QAction("退出",this);

    connect(mShowMainAction,SIGNAL(triggered()),this,SLOT(on_ShowMainAction()));
    connect(mExitAction,SIGNAL(triggered()),this,SLOT(on_ExitAction()));

    mMenu = new QMenu(this);
    mMenu->addAction(mShowMainAction);
    mMenu->addAction(mExitAction);
    mMenu->addSeparator();

    mSysTrayIcon->setContextMenu(mMenu);
    //-----flash
    IfFlash = true;
    Iconflash = true;
    mTimer = new QTimer(this);
    mTimer->start(1000);
    connect(mTimer,SIGNAL(timeout()),this,SLOT(TrayIconFlash()));


}
void MainWindow::TrayIconFlash(){
    if(Iconflash){
        mSysTrayIcon->setIcon(icon);
    }
    else{
        mSysTrayIcon->setIcon(icon2);
    }
    Iconflash = !Iconflash;

    ui->label->setText("hadf"+QString::number(Iconflash));

    ui->label_4->setText( QString::number(sub_show->pos().x())+","+
                          QString::number(sub_show->pos().y()) );
}
void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(sub2);
}


void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(sub1);

}


void MainWindow::on_pushButton_4_clicked()
{

    this->hide();

    mSysTrayIcon->show();


}
void MainWindow::on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason){
    switch (reason) {
    case QSystemTrayIcon::Trigger:
           TrayIconFlash();
        //this->show();
        //mSysTrayIcon->showMessage("提示","欢迎使用",QSystemTrayIcon::Information,1000);
        break;
    case QSystemTrayIcon::DoubleClick:
        this->show();
        break;
    default:
        break;
    }
}
void MainWindow::on_ShowMainAction(){
    this->show();
}
void MainWindow::on_ExitAction(){
    exit(0);
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_checkBox_4_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked){
        sub_show->hide();
    }
    else{
        sub_show->show();
    }
}


void MainWindow::on_checkBox_stateChanged(int arg1)
{
    //点击穿透
    if(arg1){
        SetWindowLong(sub_show->thisWinId,
                      GWL_EXSTYLE,
                      GetWindowLong(
                          sub_show->thisWinId, GWL_EXSTYLE)
                      |WS_EX_TRANSPARENT);
    }
    else{
        SetWindowLong(sub_show->thisWinId,
                      GWL_EXSTYLE,
                      GetWindowLong(
                          sub_show->thisWinId, GWL_EXSTYLE)&
                      (~WS_EX_TRANSPARENT));
    }
}


void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    //半透明
    if(arg1){
        ui->horizontalSlider->setEnabled(false);
    }
    else{
        ui->horizontalSlider->setEnabled(true);
    }
}


void MainWindow::on_checkBox_3_stateChanged(int arg1)
{
    //置顶
    if(arg1){
        if(ui->checkBox_5->isChecked()){
            ui->checkBox_5->setChecked(false);
        }
        SetWindowPos(sub_show->thisWinId,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
    }
    else{
        SetWindowPos(sub_show->thisWinId,HWND_NOTOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
    }
}
void MainWindow::on_checkBox_5_stateChanged(int arg1)
{
    //置底
    if(arg1){
        if(ui->checkBox_3->isChecked()){
            ui->checkBox_3->setChecked(false);
        }
//        HWND desktopHwnd = findDesktopIconWnd();
//        if(desktopHwnd){

//        }
        //SetWindowPos(sub_show->thisWinId,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
        SetWindowPos(sub_show->thisWinId,HWND_BOTTOM,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
    }
    else{

        SetWindowPos(sub_show->thisWinId,HWND_NOTOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
    }
}



void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->label_3->setText(QString::number(value));
    sub_show->change_transparent(value);
}
void MainWindow::on_checkBox_6_stateChanged(int arg1)
{
    if(arg1){
        ui->horizontalSlider_2->setEnabled(false);
    }
    else{
        ui->horizontalSlider_2->setEnabled(true);
    }
}
void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    ui->label_6->setText(QString::number(value));
    sub_show->change_size(value);
}
BOOL enumUserWindowsCB(HWND hwnd,LPARAM lParam)
{
    long wflags = GetWindowLong(hwnd, GWL_STYLE);
    if(!(wflags & WS_VISIBLE)) return TRUE;
    HWND sndWnd;
    if( !(sndWnd=FindWindowEx(hwnd, NULL, L"SHELLDLL_DefView", NULL)) ) return TRUE;
    HWND targetWnd;
    if( !(targetWnd=FindWindowEx(sndWnd, NULL, L"SysListView32", L"FolderView")) ) return TRUE;
    HWND* resultHwnd = (HWND*)lParam;
    *resultHwnd = targetWnd;
    return FALSE;
}

HWND findDesktopIconWnd(){
    HWND resultHwnd = NULL;
    EnumWindows((WNDENUMPROC)enumUserWindowsCB, (LPARAM)&resultHwnd);
    return resultHwnd;
}

void MainWindow::on_pushButton_5_clicked()
{
    sub_show->move(0,574);
}





void MainWindow::on_radioButton_clicked()
{
    if(ui->radioButton->isChecked()){
        sub_show->setActionMode(0);
    }
}


void MainWindow::on_radioButton_2_clicked()
{
    if(ui->radioButton_2->isChecked()){
        sub_show->setActionMode(1);
    }
}


void MainWindow::on_radioButton_3_clicked()
{
    if(ui->radioButton_3->isChecked()){
        sub_show->setActionMode(2);
    }
}

