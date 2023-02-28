#ifndef REMINDER_H
#define REMINDER_H
//时钟提醒功能
#include <QWidget>
#include <QTimer>
#include <QDateTime>
namespace Ui {
class reminder;
}

class reminder : public QWidget
{
    Q_OBJECT

public:
    explicit reminder(QWidget *parent = nullptr);
    ~reminder();
    QDateTime *datetime;
    QTimer *mTimer;

    QTime startTime;
    QTime endTime;
    QTime lessTime;
    bool ifstart;
    bool ifpause;
    int pecent;
    int sumTimeSec(const QTime t);
    const QTime timeAdd(QTime& t1,QTime& t2);
    const QTime timeSub(QTime& t1,QTime& t2);
private slots:
    void UpdateTime();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_timeEdit_2_userTimeChanged(const QTime &time);

    void on_timeEdit_userTimeChanged(const QTime &time);

    void on_horizontalSlider_valueChanged(int value);

//    void on_timeEdit_2_timeChanged(const QTime &time);

private:
    Ui::reminder *ui;

signals:
    void reminder_timeout(QTime sum);
};

#endif // REMINDER_H
