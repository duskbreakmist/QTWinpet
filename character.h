#ifndef CHARACTER_H
#define CHARACTER_H

#include <QWidget>
#include <QMovie>
#include "action.h"
#include <stable.h>

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
    void setAction(action* act);
    QPoint screenPos;
    QSize NowSize;
    double NowScale;
    HWND thisWinId;

private slots:
    void Automove();
private:
    Ui::character *ui;

    bool mouse_clicked_flag;

    QTimer * mTimer;
    action actions[10];
    action* nowaction;
    QString nowImgDir;
protected:
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent* event);
};

#endif // CHARACTER_H
