#ifndef BACKGROUNDCONTROL_H
#define BACKGROUNDCONTROL_H

#include <QWidget>

namespace Ui {
class backgroundcontrol;
}

class backgroundcontrol : public QWidget
{
    Q_OBJECT

public:
    explicit backgroundcontrol(QWidget *parent = nullptr);
    ~backgroundcontrol();

private:
    Ui::backgroundcontrol *ui;
};

#endif // BACKGROUNDCONTROL_H
