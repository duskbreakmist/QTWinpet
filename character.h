#ifndef CHARACTER_H
#define CHARACTER_H

#include <QWidget>
#include <QMovie>

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
    void Automove();
    HWND thisWinId;
private:
    Ui::character *ui;

    bool mouse_clicked_flag;
    QPoint screenPos;



protected:
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
};

#endif // CHARACTER_H
