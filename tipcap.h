#ifndef TIPCAP_H
#define TIPCAP_H

#include <QWidget>
#include "stable.h"
namespace Ui {
class tipcap;
}

class tipcap : public QWidget
{
    Q_OBJECT

public:
    explicit tipcap(QWidget *parent = nullptr);
    ~tipcap();
    QString VoiceFolder;
    QString CaptionFile;
    QStringList VoiceTime;
    QStringList Captions;
    int CaptionNum;

    bool setCaptionVoice(QPoint LUpoint);
    bool readCaption();

private slots:
    void WindowHide();

private:
    Ui::tipcap *ui;

    QTimer *mytimer;
};

#endif // TIPCAP_H
