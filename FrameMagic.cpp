#include "FrameMagic.h"
#include "ui_FrameMagic.h"

FrameMagic::FrameMagic(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::FrameMagic)
{
    ui->setupUi(this);
}

FrameMagic::~FrameMagic()
{
    delete ui;
}
