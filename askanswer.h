#ifndef ASKANSWER_H
#define ASKANSWER_H
//可输入输出对话窗口
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

    void on_textEdit_2_textChanged();

    void on_pushButton_7_clicked();

private:
    Ui::AskAnswer *ui;


};
bool CreateFolder(QString Floder);

#endif // ASKANSWER_H
