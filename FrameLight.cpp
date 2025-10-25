#include "FrameLight.h"
#include "ui_FrameLight.h"

FrameLight::FrameLight(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::FrameLight)
{
    ui->setupUi(this);
    ui->frameKeyboard->showFlag(false) ;
}

FrameLight::~FrameLight()
{
    delete ui;
}
