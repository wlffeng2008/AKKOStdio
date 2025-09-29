#include "FrameKeySetting.h"
#include "ui_FrameKeySetting.h"

FrameKeySetting::FrameKeySetting(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::FrameKeySetting)
{
    ui->setupUi(this);
}

FrameKeySetting::~FrameKeySetting()
{
    delete ui;
}
