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

    connect(ui->frameLEDBright,&ModuleEfLumi::onBrightChanged,this,[=](int bright){
        DialogDeviceConnect::instance()->setLEDBright(bright);
    });
    connect(ui->frameLEDSpeed,&ModuleEfSpeed::onSpeedChanged,this,[=](int speed){
        DialogDeviceConnect::instance()->setLEDSpeed(speed);
    });
    connect(ui->frameLEDColor,&ModuleEfColor::onSetColor,this,[=](const QColor&color){
        DialogDeviceConnect::instance()->setLEDColor(color);
    });
}

FrameLight::~FrameLight()
{
    delete ui;
}
