#include "SuperLabel.h"
#include <QEvent>

static SuperLabel *g_pLastFoucus = nullptr;

SuperLabel::SuperLabel(QWidget *parent)
    : QLabel{parent}
{
    QTimer::singleShot(100,this,[=]{
        tooltip = new CustomTooltip(this);
        tooltip->setText(this->toolTip()) ;
        timer = new QTimer(this) ;
        timer->setSingleShot(true);
        timer->setInterval(100);
        m_bEmpty = this->toolTip().isEmpty() ;
        setToolTip("") ;
        connect(timer, &QTimer::timeout, this, [=]() {
            if(m_bEmpty)
                return ;
            QPoint pos = mapToGlobal(QPoint(width()+5,(height() - tooltip->height())/2));
            tooltip->move(pos);
            tooltip->show();
        });
    });
}

bool SuperLabel::event(QEvent *event)
{
    switch (event->type())
    {
    case QEvent::Enter:
        timer->start();
        break;
    case QEvent::Leave:
        timer->stop();
        tooltip->hide();
        break;
    case QEvent::MouseButtonPress:
        tooltip->hide();
        break;
    default:
        break;
    }
    return QLabel::event(event);
}

void SuperLabel::setOwnSheet(const QString&strGetfocus,const QString&strLostfocus)
{
    m_strSheetGetfocus = strGetfocus ;
    m_strSheetLostfocus= strLostfocus ;
}

void SuperLabel::setImages(const QString&strGetfocus, const QString&strLostfocus)
{
    m_strGetfocus = strGetfocus;
    m_strLostfocus = strLostfocus;
    setFocus(false) ;
}

void SuperLabel::setFocus(bool foucs)
{
    if(foucs && g_pLastFoucus == this)
        return ;

    m_bFoucs = foucs ;
    setPixmap(QPixmap(foucs ? m_strGetfocus : m_strLostfocus));
    setStyleSheet(foucs ? m_strSheetGetfocus : m_strSheetLostfocus);
    if(!foucs)
        return ;

    if(g_pLastFoucus)
        g_pLastFoucus->setFocus(false) ;
    g_pLastFoucus = this ;
}
