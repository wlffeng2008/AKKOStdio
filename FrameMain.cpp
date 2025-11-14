#include "FrameMain.h"
#include "ui_FrameMain.h"

#include "DialogDeviceConnect.h"

#include <QTimer>
#include <QButtonGroup>

FrameMain::FrameMain(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::FrameMain)
{
    ui->setupUi(this);

    ui->labelPriv->installEventFilter(this);
    ui->labelNext->installEventFilter(this);
    
    connect(ui->frameLEDMode,&ModuleEfMode::onModeChanged,this,[=](int mode){
        DialogDeviceConnect::instance()->setLEDMode(mode);
    });
    connect(ui->frameLEDBright,&ModuleEfLumi::onBrightChanged,this,[=](int bright){
        DialogDeviceConnect::instance()->setLEDBright(bright);
    });
    connect(ui->frameLEDSpeed,&ModuleEfSpeed::onSpeedChanged,this,[=](int speed){
        DialogDeviceConnect::instance()->setLEDSpeed(speed);
    });
}

FrameMain::~FrameMain()
{
    delete ui;
}

bool FrameMain::eventFilter(QObject*watched,QEvent*event)
{
    if(event->type() == QEvent::MouseButtonRelease)
    {
        if(watched == ui->labelPriv)
        {
            return true ;
        }

        if(watched == ui->labelNext)
        {
            return true ;
        }
    }
    return QFrame::eventFilter(watched,event);
}
