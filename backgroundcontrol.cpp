#include "backgroundcontrol.h"
#include "ui_backgroundcontrol.h"

backgroundcontrol::backgroundcontrol(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::backgroundcontrol)
{
    ui->setupUi(this);
}

backgroundcontrol::~backgroundcontrol()
{
    delete ui;
}
