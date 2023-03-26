#include "workclock.h"

#include "ui_workclock.h"
bool enumUserWindowsCB(HWND hwnd, LPARAM lParam)
{
    long wflags = GetWindowLong(hwnd, GWL_STYLE);
    if (!(wflags & WS_VISIBLE)) {
        return TRUE;
    };

    HWND sndWnd;
    if (!(sndWnd=FindWindowEx(hwnd, NULL, L"SHELLDLL_DefView", NULL))) {
        return TRUE;
    }
    HWND targetWnd;
    if (!(targetWnd=FindWindowEx(sndWnd, NULL, L"SysListView32", L"FolderView"))) {
        return TRUE;
    }

    HWND* resultHwnd = (HWND*)lParam;
    *resultHwnd = targetWnd;
    return FALSE;
}

void setParentDesktop(QWidget *pWidget)
{
    HWND resultHwnd = NULL;
    EnumWindows((WNDENUMPROC)enumUserWindowsCB, (LPARAM)&resultHwnd);

    // 设置桌面为父窗口
    if (resultHwnd) {
        SetParent((HWND)pWidget->winId(), resultHwnd);
    }
}
timeblock::timeblock(float s,float e, QColor c,QString des){
    start = s;
    end = e;
    color = c;
    interval = e-s;
    startangle = 30-end;
    endangle = 30-start;
    if(startangle>24){startangle-=24;}
    if(endangle>24){endangle-=24;}
    startangle*= 15;
    endangle*= 15;
    describe = des;
    qDebug()<<startangle<<endangle;
}

void workclock::init() {
    int trans = 155;
    hourColor = QColor(200, 100, 0, trans);
    minuteColor= QColor(0, 127, 127, trans);
    secondColor= QColor(0, 160, 230, trans);
    bkColor = QColor(255,255,255);

    colors.append(QColor(0,  233,12 ,trans));//sleep
    colors.append(QColor(100,123,222,trans));//work
    colors.append(QColor(222,223,122,trans));//play
    colors.append(QColor(232,153,152,trans));//space.eat
    colors.append(QColor(23 ,213,212,trans));//unknown

    timeblocks.append(timeblock(0,7  ,colors[0]));
    timeblocks.append(timeblock(7,8  ,colors[3]));
    timeblocks.append(timeblock(8,12 ,colors[1]));
    timeblocks.append(timeblock(12,13,colors[3]));
    timeblocks.append(timeblock(13,14,colors[0]));
    timeblocks.append(timeblock(14,17,colors[1]));
    timeblocks.append(timeblock(17,18,colors[3]));
    timeblocks.append(timeblock(18,19,colors[2]));
    timeblocks.append(timeblock(19,23,colors[1]));
    timeblocks.append(timeblock(23,24,colors[2]));



}
workclock::workclock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::workclock)
{
    ui->setupUi(this);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);

    time = QTime::currentTime();
    mode = 1;
    rect = QRect(0,0,width(),height());
    rectrange = 80;
    init();



    setWindowFlag(Qt::Tool);
    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    SetWindowLong((HWND)winId(),
                  GWL_EXSTYLE,
                  GetWindowLong(
                      (HWND)winId(), GWL_EXSTYLE)
                  |WS_EX_TRANSPARENT);
    SetWindowPos((HWND)winId(),HWND_BOTTOM,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);

    setParentDesktop(this);
    setWindowOpacity(0.7);
}

workclock::~workclock()
{
    colors.clear();
    timeblocks.clear();
    delete ui;

}
void workclock::painttimeblocks(QPainter &p){

    int s=0,interval=0;
    for(int i=0;i<timeblocks.length();i++){
        //p.setBrush()
        s = timeblocks[i].startangle*16;
        interval = timeblocks[i].interval*15*16;
        //e = timeblocks[i].endangle*16;
        //qDebug()<<s<<e;
        p.setPen(Qt::NoPen);
        p.setBrush(timeblocks[i].color);
        p.drawPie(-100,-100,200,200,s,interval);
//
//        p.drawPie(-50,-50,100,100,s,e);
    }
    p.setBrush(bkColor);
    p.drawPie(-1*rectrange,-1*rectrange,2*rectrange,2*rectrange,0,5760);
}
QRectF workclock::textRectF(double radius, int pointSize, double angle)
{
    QRectF rectF;
    rectF.setX(radius*qCos(angle*M_PI/180.0) - pointSize*2);
    rectF.setY(radius*qSin(angle*M_PI/180.0) - pointSize/2.0);
    rectF.setWidth(pointSize*4);
    rectF.setHeight(pointSize);
    return rectF;
}
void workclock::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    static const QPoint hourHand[4] = {
        QPoint(3, 2),
        QPoint(-3, 2),
        QPoint(-1, -60),
        QPoint(1, -60)
    };
    static const QPoint minuteHand[3] = {
        QPoint(2, 2),
        QPoint(-2, 2),
        QPoint(0, -70)
    };

    static const QPoint secondHand[3] = {
        QPoint(2, 2),
        QPoint(-2, 2),
        QPoint(0, -80)//0~100
    };
    side = qMin(width(), height());
    hour = time.currentTime().hour();
    min = time.currentTime().minute();
    sec = time.currentTime().second();
    rect = QRect(0,0,width(),height());
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    // 平移坐标系原点至中心点
    painter.translate(width() / 2, height() / 2);
    // 缩放
    painter.scale(side / 200.0, side / 200.0);

    painttimeblocks(painter);

    painter.setPen(Qt::NoPen);
    painter.setBrush(hourColor);
    if(mode){
        painter.save();
        painter.rotate(15.0 * (( hour+ min / 60.0)));
        painter.drawConvexPolygon(hourHand, 4);
        painter.restore();

        painter.setPen(QColor(0,0,0));

        // 绘制小时线 （360度 / 24 = 15度）
        for (int i = 0; i < 24; ++i) {
            painter.drawLine(88, 0, 96, 0);
            painter.rotate(15.0);
        }
        int radius = 100;
        QFont font = painter.font();
        //font.setBold(true);
        painter.setFont(font);
        int pointSize = font.pointSize();

        // 绘制小时文本

        for (int i = 0; i < 24; ++i) {
            painter.drawText(textRectF(radius*0.8, pointSize, (i-6) * 15), Qt::AlignCenter, QString::number(i));
        }

    }
    else{
         //绘制时针
        painter.save();
        // 每圈360° = 12h 即：旋转角度 = 小时数 * 30°
        painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
        painter.drawConvexPolygon(hourHand, 3);
        painter.restore();

        painter.setPen(hourColor);

        // 绘制小时线 （360度 / 12 = 30度）
        for (int i = 0; i < 12; ++i) {
            painter.drawLine(88, 0, 96, 0);
            painter.rotate(30.0);
        }

        int radius = 100;
        QFont font = painter.font();
        //font.setWeight(Weight())
        font.setBold(true);
        painter.setFont(font);

        int pointSize = font.pointSize();

        // 绘制小时文本
        int nHour = 0;
        for (int i = 0; i < 12; ++i) {
            nHour = i + 3;
            if (nHour > 12)
                nHour -= 12;
            painter.drawText(textRectF(radius*0.8, pointSize, i * 30), Qt::AlignCenter, QString::number(nHour));
        }
    }
    // 绘制分针
    painter.setPen(Qt::NoPen);
    painter.setBrush(minuteColor);
    painter.save();
    // 每圈360° = 60m 即：旋转角度 = 分钟数 * 6°
    painter.rotate(6.0 * (min + sec / 60.0));
    painter.drawConvexPolygon(minuteHand, 3);
    painter.restore();
    painter.setPen(minuteColor);

    // 绘制分钟线 （360度 / 60 = 6度）
    for (int j = 0; j < 60; ++j) {
        if ((j % 5) != 0)
            painter.drawLine(92, 0, 96, 0);
        painter.rotate(6.0);
    }

    // 绘制秒针
    painter.setPen(Qt::NoPen);
    painter.setBrush(secondColor);

    painter.save();
    // 每圈360° = 60s 即：旋转角度 = 秒数 * 6°
    painter.rotate(6.0 * sec);
    painter.drawConvexPolygon(secondHand, 3);
    painter.restore();
}


