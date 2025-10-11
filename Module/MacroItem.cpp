#include "MacroItem.h"
#include "ui_MacroItem.h"

MacroItem::MacroItem(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::MacroItem)
{
    ui->setupUi(this);
    setCursor(Qt::PointingHandCursor) ;

    connect(ui->pushButtonEdit,&QPushButton::clicked,this,[=]{emit onOperation(0,this);}) ;
    connect(ui->pushButtonDelete,&QPushButton::clicked,this,[=]{emit onOperation(1,this);}) ;
}

MacroItem::~MacroItem()
{
    delete ui;
}

bool MacroItem::event(QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress)
    {
        setStyleSheet("QFrame { background-color: #F6F6F6; border-radius: 4px;}");
        return true;
    }
    return QFrame::event(event) ;
}
