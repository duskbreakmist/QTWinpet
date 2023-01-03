#ifndef PROCESSLIST_H
#define PROCESSLIST_H

#include <QWidget>
#include "stable.h"
namespace Ui {
class processlist;
}

class processlist : public QWidget
{
    Q_OBJECT

public:
    explicit processlist(QWidget *parent = nullptr);
    ~processlist();
    void showProcess();
    bool IfUpdate;
private slots:
    void on_pushButton_update_clicked();
    void Update();
    void on_pushButton2_clicked();

private:
    Ui::processlist *ui;
    QTimer *mTimer;

};

#endif // PROCESSLIST_H
