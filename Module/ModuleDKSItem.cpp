#include "ModuleDKSItem.h"
#include "ui_ModuleDKSItem.h"

#include <QPainter>
#include <QMouseEvent>

ModuleDKSItem::ModuleDKSItem(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::ModuleDKSItem)
{
    ui->setupUi(this);

    ui->labelSwitch1->installEventFilter(this);
    ui->labelSwitch2->installEventFilter(this);
    ui->labelSwitch3->installEventFilter(this);
    ui->labelSwitch4->installEventFilter(this);
    setMouseTracking(true) ;

    connect(&m_TMReset,&QTimer::timeout,this,[=]{
        if(!m_dragging)
        {
            m_TMReset.stop();
            m_dragX1 = 0;
        }
    });
}

ModuleDKSItem::~ModuleDKSItem()
{
    delete ui;
}

bool ModuleDKSItem::eventFilter(QObject*watched,QEvent*event)
{
    if(event->type() == QEvent::MouseButtonRelease)
    {
        m_dragging = false ;
        QList<QLabel*> labels={ui->labelSwitch1,ui->labelSwitch2,ui->labelSwitch3,ui->labelSwitch4};
        for(int i=0; i<4; i++)
        {
            if(watched == labels[i])
            {
                m_switchs[i] = !m_switchs[i];
                labels[i]->setPixmap(QPixmap(m_switchs[i]?":/images/k/ic_selected.png":":/images/k/ic_add.png"));
                return true ;
            }
        }
    }

    return QFrame::eventFilter(watched, event);
}

bool ModuleDKSItem::event(QEvent*event)
{
    QMouseEvent *pMEvent = static_cast<QMouseEvent *>(event) ;
    if(event->type() == QEvent::MouseButtonPress)
    {
        if(m_dragX1 == 0)
            m_dragX1 = pMEvent->pos().x() ;
        m_dragging = true ;
    }
    if(event->type() == QEvent::MouseButtonRelease)
    {
        m_dragging = false ;
    }

    if(event->type() == QEvent::MouseMove && m_dragging)
    {
        m_TMReset.stop() ;
        m_dragX2 = pMEvent->pos().x() ;
        QList<QLabel*> labels={ui->labelSwitch1,ui->labelSwitch2,ui->labelSwitch3,ui->labelSwitch4};
        for(int i=0; i<4; i++)
        {
            QRect rc = labels[i]->geometry() ;
            if(rc.right()<m_dragX2 && rc.left()>m_dragX1)
                labels[i]->hide();
            else
                labels[i]->show();
        }

        bool allshow = true;
        for(int i=0; i<4; i++)
        {
            if(labels[i]->isHidden())
            {
                allshow = false;
                break;
            }
        }
        if(allshow)
        {
            m_dragX2=0;
            m_TMReset.start(500) ;
        }

        update() ;
    }

    return QFrame::event(event);
}


void ModuleDKSItem::paintEvent(QPaintEvent*event)
{
    QPainter painter(this) ;
    painter.setRenderHint(QPainter::Antialiasing);

    int x1 = m_dragX1;
    int x2 = m_dragX2;

    if(x1<140) x1 = 140;
    if(x2>382) x2 = 382;

    int nW = x2-x1 ;
    if(nW<10)
    {
        QFrame::paintEvent(event);
        return ;
    }

    QRect rect(x1,8,nW,24) ;
    painter.setPen(0x6329B6) ;
    painter.setBrush(0x6329B6) ;
    painter.drawRoundedRect(rect,12,12);
    painter.drawPixmap(rect.right()-20,10,QPixmap(":/images/k/ic_selected.png"));
}
