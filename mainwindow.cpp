#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setWindowTitle("控制面板");


    CharacterNum = 0;
    sub1 = new processlist;
    sub2 = new wininfo;
    sub3 = new backgroundcontrol;
    ui->textEdit->setText("./character/斯卡蒂皮肤");

    Create_character();

    ui->horizontalSlider->setRange(0,100);
    ui->horizontalSlider_2->setRange(10,100);
    ui->horizontalSlider->setValue(79);
    ui->horizontalSlider_2->setValue(58);
//    ui->checkBox_2->setChecked(true);
//    ui->checkBox_6->setChecked(true);
    ui->checkBox_4->setChecked(false);
    ui->checkBox_3->setChecked(true);
    ui->stackedWidget->addWidget(sub1);
    ui->stackedWidget->addWidget(sub2);
    ui->stackedWidget->addWidget(sub3);
    ui->stackedWidget->setCurrentWidget(sub1);
    ui->stackedWidget->setCurrentIndex(0);

    //------
    Create_TrayIcon();
    //-----

//    connect(mReminder, SIGNAL(reminder_timeout(QTime )), this,
//            SLOT(mSysTrayIcon->showMessage("提示","欢迎使用",QSystemTrayIcon::Information,1000);));


    on_pushButton_4_clicked();

    nowclock = new workclock;
    nowclock->show();
}

MainWindow::~MainWindow()
{
    sub1->~processlist();//记得！
    sub2->~wininfo();
    sub3->~backgroundcontrol();
    delete sub1;
    delete sub2;
    delete sub3;
    delete nowclock;
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
        sub_show->hide();
        sub_show->show();
        break;
//    case QSystemTrayIcon::Trigger:
//           TrayIconFlash();
//        //this->show();
//        mSysTrayIcon->showMessage("提示","欢迎使用",QSystemTrayIcon::Information,1000);
//        break;
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

        SetWindowPos(sub_show->thisWinId,HWND_BOTTOM,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
    }
    else{

        SetWindowPos(sub_show->thisWinId,HWND_NOTOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
    }
}



void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    //透明度
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
    //大小
    ui->label_6->setText(QString::number(value));
    sub_show->change_size(value);
}
//寻找桌面
//BOOL enumUserWindowsCB(HWND hwnd,LPARAM lParam)
//{
//    long wflags = GetWindowLong(hwnd, GWL_STYLE);
//    if(!(wflags & WS_VISIBLE)) return TRUE;
//    HWND sndWnd;
//    if( !(sndWnd=FindWindowEx(hwnd, NULL, L"SHELLDLL_DefView", NULL)) ) return TRUE;
//    HWND targetWnd;
//    if( !(targetWnd=FindWindowEx(sndWnd, NULL, L"SysListView32", L"FolderView")) ) return TRUE;
//    HWND* resultHwnd = (HWND*)lParam;
//    *resultHwnd = targetWnd;
//    return FALSE;
//}

//HWND findDesktopIconWnd(){
//    HWND resultHwnd = NULL;
//    EnumWindows((WNDENUMPROC)enumUserWindowsCB, (LPARAM)&resultHwnd);
//    return resultHwnd;
//}

void MainWindow::on_pushButton_5_clicked()
{
    sub_show->reset();
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

bool MainWindow::Create_character(){
    if(CharacterNum>=MaxCharacterNum){
        qDebug()<<">max character";
        return false;
    }
    QListWidgetItem *item = new QListWidgetItem;
    character* temp = new character;
    temp->ControlWindow = this;
    item->setText(QString::number(CharacterNum));
    item->setData(Qt::UserRole,QVariant::fromValue((void *) temp));
    ui->listWidget->addItem(item);
    NowItem = item;
    sub_show = temp;
    sub_show->UpdateFolder(CharacterFolder);

    CharacterNum++;
    ui->label_11->setText(QString::number(CharacterNum));
    ui->label_13->setText(item->text());

    sub_show->show();//这个必须有

    //初始化用
    SetWindowPos(sub_show->thisWinId,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
    sub_show->change_transparent(ui->horizontalSlider->value());
    sub_show->change_size(ui->horizontalSlider_2->value());


    return true;
}
void MainWindow::on_pushButton_7_clicked()
{
    //add character
    Create_character();

}
void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    //选中角色
    NowItem = item;
    ui->label_13->setText(item->text());
    sub_show = (character*) item->data(Qt::UserRole).value<void *>();
}

void MainWindow::on_pushButton_6_clicked()
{
    //删除角色
    if(CharacterNum>1){
        sub_show->close();
        delete sub_show;
        ui->listWidget->removeItemWidget(NowItem);
        delete NowItem;
        CharacterNum--;
        NowItem =  ui->listWidget->item(CharacterNum-1);
        ui->label_13->setText(NowItem->text());
        sub_show = (character*)NowItem->data(Qt::UserRole).value<void *>();
        ui->label_11->setText(QString::number(CharacterNum));
    }
}


void MainWindow::on_textEdit_textChanged()
{
    //修改character文件路径
    CharacterFolder = ui->textEdit->toPlainText();
}


void MainWindow::on_pushButton_8_clicked()
{
    //浏览文件夹
    QString folder = QFileDialog::getExistingDirectory(this, "选择目录", "./", QFileDialog::ShowDirsOnly);
    if(!folder.isNull()){
        ui->textEdit->setText(folder);
    }
}
void MainWindow::on_pushButton_9_clicked()
{
    //更改当前
    sub_show->UpdateFolder(CharacterFolder);
}


void MainWindow::on_pushButton_10_clicked()
{
    ui->stackedWidget->setCurrentWidget(sub3);
}


void MainWindow::on_checkBox_7_clicked(bool checked)
{
    if(checked){
        nowclock->hide();
    }
    else{
        nowclock->show();
    }
}

