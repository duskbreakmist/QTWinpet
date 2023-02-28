#ifndef TIPCAP_H
#define TIPCAP_H

//显示对话气泡的。
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

    QStringList VoicePath;
    QStringList VoiceTime;
    QStringList Captions;
    int CaptionNum;

    bool setCaptionVoice(QPoint LUpoint);
    bool readCaption();
    void UpdateFolder(QString nowfolder);
private slots:
    void WindowHide();

private:
    Ui::tipcap *ui;
    QSoundEffect* soundeffect;
    QTimer *mytimer;
};

#endif // TIPCAP_H
