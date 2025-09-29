#include "FrameMain.h"
#include "ui_FrameMain.h"
#include <QTimer>

#include <QButtonGroup>

FrameMain::FrameMain(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::FrameMain)
{
    ui->setupUi(this);
}

FrameMain::~FrameMain()
{
    delete ui;
}
