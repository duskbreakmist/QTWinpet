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
    ifloop = true;
}

backgroundcontrol::~backgroundcontrol()
{
    delete ui;
    closeSubDesktop();
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
void backgroundcontrol::closeSubDesktop(){
    if(hffplay!=0){
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

void backgroundcontrol::on_pushButton_2_clicked()
{
    //set
    //记得留空格！！！
    QString temp = " "+ui->lineEdit->text()+ " -noborder -x 1920 -y 1080";
    if(ifloop){
        temp += " -loop 0";
    }
    else{
        temp += " -loop 1";
    }
    temp.replace("/","\\");
    qDebug()<<"get";
    qDebug()<<temp.toStdWString();
    lpParam = temp.toStdWString().c_str();
    createSubDesktop();
}


void backgroundcontrol::on_pushButton_3_clicked()
{
    //close
    closeSubDesktop();
}


void backgroundcontrol::on_pushButton_clicked()
{
    QString folder = QFileDialog::getOpenFileName(this, "选择目录");
//::getExistingDirectory(this, "选择目录", "./", QFileDialog::ShowDirsOnly);
    ui->lineEdit->setText(folder);
}

