#include "FrameAbout.h"
#include "ui_FrameAbout.h"

FrameAbout::FrameAbout(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::FrameAbout)
{
    ui->setupUi(this);
}

FrameAbout::~FrameAbout()
{
    delete ui;
}
