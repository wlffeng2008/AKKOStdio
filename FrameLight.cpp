#include "FrameLight.h"
#include "ui_FrameLight.h"

#include "DialogDeviceConnect.h"

FrameLight::FrameLight(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::FrameLight)
{
    ui->setupUi(this);
    ui->frameKeyboard->showFlag(false) ;

    connect(ui->frameLEDMode,&ModuleEfMode::onModeChanged,this,[=](int mode){
        DialogDeviceConnect::instance()->setLEDMode(mode);
    });
}

FrameLight::~FrameLight()
{
    delete ui;
}
