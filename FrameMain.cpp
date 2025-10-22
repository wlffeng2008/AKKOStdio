#include "FrameMain.h"
#include "ui_FrameMain.h"

#include <QTimer>
#include <QButtonGroup>

FrameMain::FrameMain(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::FrameMain)
{
    ui->setupUi(this);

    ui->labelPriv->installEventFilter(this);
    ui->labelNext->installEventFilter(this);
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
