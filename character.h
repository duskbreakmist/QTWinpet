#ifndef CHARACTER_H
#define CHARACTER_H
//显示角色图片的窗口
#include <QWidget>
#include <QMovie>
#include "action.h"
#include <stable.h>
#include "tipcap.h"
#include "askanswer.h"
#include "reminder.h"

#define SCREENwidth 250
#define SCREENheight 250
namespace Ui {
class character;
}

class character : public QWidget
{
    Q_OBJECT

public:
    explicit character(QWidget *parent = nullptr);
    ~character();
    QWidget* ControlWindow;

    void UpdateFolder(QString nowfolder);
    QString characterFolder;
    void change_state(int i);
    void change_transparent(int i);
    void change_size(int i);

    void AutoRisize(QSize NewSize);//同时保证图片下边中点不变。
    QSize NowSize;//配合上面的函数使用//现在的显示图片大小//窗口大小不变了
    double NowScale;//配合上面
    QPoint StableP;//配合上面

    void setAction(action* act);
    void setActionMode(int i);
    QPoint screenPos;//鼠标点击的全局坐标

    HWND thisWinId;
    //物理部分

    QPointF m_v;
    QPointF m_g;
    QPointF m_p;
    int ground_y;
    bool IfFloat;
    bool IfPhy;
    char loopval;//为了分频而做
    void reset();



private slots:
    bool Automove();
    //void AutoPicUpdate();
private:
    Ui::character *ui;
    AskAnswer *sub_ask;
    tipcap * TipCaption;
    reminder* mReminder;
    //bool mouse_clicked_flag;
    bool mouse_clicked_R;
    bool mouse_moved_R;
    bool mouse_clicked_L;
    bool mouse_moved_L;
    bool IfRLTurn;//true== walk left
    QTimer * mTimer_pos;


    action actions[7];
    action* nowaction;
    int ActionMode;

    //QMediaPlayer *player;
    QSoundEffect* soundeffect;

    double NextAngle;
    int NextWidget;
    QString WidgetTip[4] = {"显示主界面",
                            "显示tool",
                            "隐藏tool",
                            "隐藏主界面"};
protected:
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent* event);
};

#endif // CHARACTER_H
