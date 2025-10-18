#include "ModuleScrollValue.h"
#include "ui_ModuleScrollValue.h"

#include <QMouseEvent>
#include <QWheelEvent >

ModuleScrollValue::ModuleScrollValue(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::ModuleScrollValue)
{
    ui->setupUi(this);
    QStringList valus = QString("A,B,C,D,D,E,F,1,2,3,4,5,6,7,8,9,0").split(',');
    setValueList(valus);

    ui->labelValue1->installEventFilter(this) ;
    ui->labelValue2->installEventFilter(this) ;
    ui->labelValue3->installEventFilter(this) ;
    ui->labelValue4->installEventFilter(this) ;
    ui->labelValue5->installEventFilter(this) ;
}

ModuleScrollValue::~ModuleScrollValue()
{
    delete ui;
}

void ModuleScrollValue::setValueList(QStringList&valus)
{
    m_Values = valus;
    m_nIndex = 1000000000 * valus.count();
    rollValues() ;
}

void ModuleScrollValue::rollValues()
{
    int count = m_Values.count();
    if(count<=0)
        return ;

    QList<QLabel*> labels =
    {
        ui->labelValue1,
        ui->labelValue2,
        ui->labelValue3,
        ui->labelValue4,
        ui->labelValue5
    };

    for(int i=0; i<5; i++)
    {
        int nX = (i + m_nIndex) % count;
        labels[i]->setText(m_Values[nX]);
    }
}

bool ModuleScrollValue::eventFilter(QObject*watched,QEvent*event)
{
    if(event->type() == QEvent::MouseButtonRelease)
    {
        int old = m_nIndex ;
        if(watched==ui->labelValue1) m_nIndex -= 2 ;
        if(watched==ui->labelValue2) m_nIndex -= 1 ;
        if(watched==ui->labelValue4) m_nIndex += 2 ;
        if(watched==ui->labelValue5) m_nIndex += 1 ;
        if(m_nIndex != old)  rollValues();
    }

    return QFrame::eventFilter(watched,event) ;
}

bool ModuleScrollValue::event(QEvent*event)
{
    if(QEvent::Wheel == event->type())
    {
        QWheelEvent  *pME = static_cast<QWheelEvent *>(event) ;

        QPoint angleDelta = pME->angleDelta();

        if (angleDelta.y() > 0)
        {
            m_nIndex -- ;
        }
        else
        {
            m_nIndex ++ ;
        }

        rollValues();

        return true ;
    }
    return QFrame::event(event) ;
}
