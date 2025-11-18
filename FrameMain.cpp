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

    ui->labelPriv->setEnabled(false) ;
    ui->labelNext->setEnabled(false) ;

    DialogDeviceConnect *pConnector = DialogDeviceConnect::instance();
    
    connect(ui->frameLEDMode,&ModuleEfMode::onModeChanged,this,[=](int mode){
        pConnector->setLEDMode(mode);
    });
    connect(ui->frameLEDBright,&ModuleEfLumi::onBrightChanged,this,[=](int bright){
        pConnector->setLEDBright(bright);
    });
    connect(ui->frameLEDSpeed,&ModuleEfSpeed::onSpeedChanged,this,[=](int speed){
        pConnector->setLEDSpeed(speed);
    });
    connect(ui->frameLEDColor,&ModuleEfColor::onSetColor,this,[=](const QColor&color){
        pConnector->setLEDColor(color);
    });

    connect(pConnector,&DialogDeviceConnect::onReadBack,[=](const QByteArray&data){
        quint8 *pPack = (quint8 *)data.data() ;
        quint8 cmd = pPack[0] ;
        qDebug() << "---------------" << cmd;
        if(cmd == CMD_GET_LEDPARAM)
        {
            ui->frameLEDMode->setEfMode(pPack[1]);
            ui->frameLEDSpeed->setSpeed(pPack[2]);
            ui->frameLEDBright->setBright(pPack[3]);
        }
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
