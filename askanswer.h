#ifndef ASKANSWER_H
#define ASKANSWER_H

#include <QWidget>
#include "stable.h"
namespace Ui {
class AskAnswer;
}

class AskAnswer : public QWidget
{
    Q_OBJECT

public:
    explicit AskAnswer(QWidget *parent = nullptr);
    ~AskAnswer();
    bool CreateFolder();
    bool SaveTxt();
    bool SaveInteraction();
    bool UpdateNowWords();
    bool IfExtend;
    QString SaveFloder;

    QString NowWords;
    HWND thisWinId;
    void change_transparent(int i);

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::AskAnswer *ui;


};

#endif // ASKANSWER_H