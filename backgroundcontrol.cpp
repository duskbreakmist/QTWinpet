#include "backgroundcontrol.h"
#include "ui_backgroundcontrol.h"
BOOL CALLBACK EnumWinProc(HWND hwnd, LPARAM lParam)
{
    HWND hDefView = FindWindowEx(hwnd, 0, L"SHELLDLL_DefView", 0);
    if (hDefView != 0) {
        HWND hWorkerw = FindWindowEx(0, hwnd, L"WorkerW", 0);
        ShowWindow(hWorkerw, SW_HIDE);
        return FALSE;
    }
    return TRUE;
}

backgroundcontrol::backgroundcontrol(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::backgroundcontrol)
{
    ui->setupUi(this);
    hffplay = 0;
    lpParam = L" C:\\Users\\ASUS\\Desktop\\test.mp4 -noborder -x 1920 -y 1080 -loop 0";
    ffplayer = L"D:\\Programs\\FFmpeg\\ffmpeg20220620full\\bin\\ffplay.exe";

    ui->lineEdit->setText("C:/Users/ASUS/Desktop/test.mp4");
    ui->lineEdit_2->setText("C:/Users/ASUS/Desktop/wallpaper/drawbymyself.png");
    staticurl = "C:\\Users\\ASUS\\Desktop\\wallpaper";
    ifloop = true;
    ifkeep = false;
    ifmusic = true;
    ifautoset = false;
    initfile= "./Data/init.txt";

    readinitfile();
    if(ifautoset){//开机启动设置
        on_pushButton_2_clicked();
    }
    //createSubDesktop();
}

backgroundcontrol::~backgroundcontrol()
{
    closeSubDesktop(!ifkeep);
    qDebug()<<ifkeep;
    delete ui;
}
void backgroundcontrol::createSubDesktop(){
    if(hffplay!=0){
        closeSubDesktop();
    }
    if (CreateProcess(ffplayer, (LPWSTR)lpParam, 0, 0, 0, CREATE_NO_WINDOW, 0, 0, &si, &pi)) //创建视频窗口进程显示视频
        {
            Sleep(1000);
            //获取桌面窗口的句柄
            HWND hProgman = FindWindow(L"Progman", 0);
            //发送0x52c消息
            SendMessage(hProgman, 0x52c, 0, 0);
            //获取视频窗口的句柄
            hffplay = FindWindow(L"SDL_app", 0);
            //将视频窗口设置为桌面窗口的子窗口
            SetParent(hffplay, hProgman);
            //枚举窗口找到WorkerW-2并隐藏它
            EnumWindows(EnumWinProc, 0);

            SetWindowLong(hffplay,
                GWL_EXSTYLE,
                GetWindowLong(
                    hffplay, GWL_EXSTYLE)
                | WS_EX_TRANSPARENT);
        }
}
void backgroundcontrol::closeSubDesktop(bool t){

    if(t&&hffplay!=0){
        //DestroyWindow(hffplay);
        TerminateProcess(pi.hProcess, 0);
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
        hffplay=0;
    }
    else{
        qDebug()<<"df";
    }
}
void backgroundcontrol::setstaticbk(){
    QString temp = ui->lineEdit_2->text();
    PVOID temp2;
    temp.replace("/","\\");
    qDebug()<<temp;
    temp2 = (PVOID)(temp.toStdString().c_str());
    qDebug()<<temp2;//这玩意会变！！！相同temp2有不同 的值。真奇怪而且好像不同值也可以正确读取
    //const char* path = "C:\\Users\\ASUS\\Desktop\\wallpaper\\img0.jpg";
//    SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, (PVOID)path, SPIF_SENDCHANGE);
    while(!SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, temp2, SPIF_SENDCHANGE||SPIF_UPDATEINIFILE)){
        qDebug()<<temp2;
    }
}
void backgroundcontrol::returnstaticbk(){

}
void backgroundcontrol::on_pushButton_2_clicked()
{
    //set
    //记得留空格！！！
    QString temp = " "+ui->lineEdit->text()+ " -alwaysontop -noborder -x 1920 -y 1080";
    if(ifloop){
        temp += " -loop 0";
    }
    else{
        temp += " -loop 1";
    }
    if(!ifmusic){
        temp+= " -an";
    }
    temp.replace("/","\\");
    qDebug()<<"get";
    qDebug()<<temp.toStdWString();
    lpParam = temp.toStdWString().c_str();

    QString temp2 = ui->lineEdit_3->text();
    temp2.replace("/","\\");
    ffplayer = temp2.toStdWString().c_str();
    qDebug()<<temp2.toStdWString();

    createSubDesktop();
}


void backgroundcontrol::on_pushButton_3_clicked()
{
    //close
    closeSubDesktop();
}


void backgroundcontrol::on_pushButton_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, "选择视频等文件");
//::getExistingDirectory(this, "选择目录", "./", QFileDialog::ShowDirsOnly);
    if(!file.isEmpty()){
        ui->lineEdit->setText(file);

    }
}


void backgroundcontrol::on_checkBox_2_clicked(bool checked)
{
    if(checked){
        ifkeep = true;
    }
    else{
        ifkeep = false;
    }
}


void backgroundcontrol::on_checkBox_3_clicked(bool checked)
{
    if(checked){
        ifmusic = true;
    }
    else{
        ifmusic = false;
    }
}


void backgroundcontrol::on_pushButton_4_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, "选择图片文件");
    if(!file.isEmpty()){
        ui->lineEdit_2->setText(file);

    }
}


void backgroundcontrol::on_pushButton_5_clicked()
{
    //set pic
    setstaticbk();
}


void backgroundcontrol::on_pushButton_6_clicked()
{
    //return pic
    returnstaticbk();
}


void backgroundcontrol::on_pushButton_7_clicked()
{
    //save
    QFile f(initfile);
    QString textEdit_txt =
            ui->lineEdit->text()
            +"\n"+ui->lineEdit_2->text()
            +"\n"+ui->lineEdit_3->text()
            +"\n"+(ifautoset?"1":"0")
            +"\n"+(ifmusic?"1":"0")
            +"\n"+(ifkeep?"1":"0");
    QByteArray log = textEdit_txt.toUtf8();
//        QByteArray log = textEdit_txt.toLocal8Bit();
    if(!f.open(QIODevice::WriteOnly)){
        qDebug()<<"f open error,文件不存在";
        f.open(QIODevice::WriteOnly);
        f.write(log,log.length());
        f.close();
    }
    else{
        qDebug()<<"add success";
        ui->label->setText("添加成功");
        f.write(log,log.length());
        f.close();
    }
}

bool backgroundcontrol::readinitfile(){
    //read
    QFile f(initfile);
    if(!f.open(QIODevice::ReadOnly)){
        qDebug()<<"f open error,文件不存在";
        f.close();
        return false;
    }
    qDebug()<<"read success";
    QTextStream * read = new QTextStream(&f);
    QStringList Data = read->readAll().split("\n");
    qDebug()<<Data.count();

    if(Data.count()!=6){
        qDebug()<<"文件损坏";
        f.close();
        return false;
    }
    //打印出每行的第一个单元格的数据
    ui->lineEdit->setText(Data.at(0));
    ui->lineEdit_2->setText(Data.at(1));
    ui->lineEdit_3->setText(Data.at(2));//播放器地址
    if(Data.at(3)=="0"){
        ifautoset = 0;
        ui->checkBox_4->setChecked(false);
    }
    else{
        ifautoset = 1;
        ui->checkBox_4->setChecked(true);
    }
    if(Data.at(4)=="0"){
        ifmusic = 0;
        ui->checkBox_3->setChecked(false);
    }
    else{
        ifmusic = 1;
        ui->checkBox_3->setChecked(true);
    }
    if(Data.at(5)=="0"){
        ifkeep= 0;
        ui->checkBox_2->setChecked(false);
    }
    else{
        ifkeep = 1;
        ui->checkBox_2->setChecked(true);
    }


    f.close();
    return true;
}

void backgroundcontrol::on_pushButton_8_clicked()
{
    readinitfile();
}


void backgroundcontrol::on_checkBox_4_clicked(bool checked)
{
    if(checked){
        ifautoset = true;
    }
    else{
        ifautoset = false;
    }
}

bool backgroundcontrol::sendMessage(int key)
{
    if(hffplay==0){
        return false;
    }
    qDebug()<<key;
    DWORD dwVKFkeyData = 0;//lParam 参数值
    WORD dwScanCode =MapVirtualKey(key,0);//获取回车虚拟按键VK_SPACE的键盘扫描码
    dwVKFkeyData = 1;
    dwVKFkeyData |= dwScanCode<<16;
    //按下
    ::PostMessage(hffplay,WM_KEYDOWN,key,dwVKFkeyData);
    //弹起
    dwVKFkeyData |= 1<<30;
    ::PostMessage(hffplay,WM_KEYUP,key,dwVKFkeyData);
    Sleep(50);
    //qDebug()<<"end";
    return true;

}
void backgroundcontrol::on_pushButton_9_clicked()
{
    //暂停
//    qDebug()<<PostMessage(hffplay, WM_KEYDOWN, 0x20, 0);//发送‘H’到notepad
//    qDebug()<<PostMessage(hffplay, WM_KEYUP, 0x20, 0);//发送‘H’到notepad
//    qDebug()<<SendMessage (hffplay, WM_KEYDOWN, 0x20, 0);//发送‘H’到notepad
//    qDebug()<<SendMessage (hffplay, WM_KEYUP, 0x20, 0);//发送‘H’到notepad

    if(hffplay!=0){
        ifpaused = !ifpaused;
        if(ifpaused){
            ui->pushButton_9->setText("已暂停");
        }
        else{
            ui->pushButton_9->setText("暂停");
        }
        sendMessage(VK_SPACE);

    }
}


void backgroundcontrol::on_pushButton_11_clicked()
{
    //回放

    sendMessage(VK_LEFT);

}


void backgroundcontrol::on_pushButton_10_clicked()
{
    //快进

    sendMessage(VK_VOLUME_DOWN);

}


void backgroundcontrol::on_pushButton_12_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, "选择exe文件");
    if(!file.isEmpty()){
        ui->lineEdit_3->setText(file);
    }
}


void backgroundcontrol::on_pushButton_13_clicked()
{
    //音量-
    sendMessage(VK_UP);
}


void backgroundcontrol::on_pushButton_14_clicked()
{
    //静音
    sendMessage(0x4D);
}


void backgroundcontrol::on_pushButton_15_clicked()
{
    //音量+
    sendMessage(VK_RIGHT);
}

