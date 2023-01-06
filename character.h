#ifndef CHARACTER_H
#define CHARACTER_H

#include <QWidget>
#include <QMovie>
#include "action.h"
#include <stable.h>
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

private slots:
    void Automove();
    void AutoPicUpdate();
private:
    Ui::character *ui;

    bool mouse_clicked_flag;
    bool IfRLTurn;//true== walk left
    QTimer * mTimer_pos;
    QTimer * mTimer_pic;

    action actions[10];
    action* nowaction;
    int ActionMode;

    //QMediaPlayer *player;
    QSoundEffect* soundeffect;
    QString nowImgDir;
protected:
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent* event);
};

#endif // CHARACTER_H
