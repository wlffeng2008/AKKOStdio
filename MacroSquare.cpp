#include "MacroSquare.h"

#include <QPainter>
#include <QEvent>
#include <QPaintEvent>
#include <QMouseEvent>

MacroSquare::MacroSquare(const QString &text, int type, QWidget *parent)
    : QWidget{parent}
{
    setCursor(Qt::PointingHandCursor) ;
    m_type = type;
    m_text = text;
}

void MacroSquare::paintEvent(QPaintEvent*event)
{
    QPainter painter(this) ;
    painter.setRenderHint(QPainter::Antialiasing) ;
    QRect rect = this->rect().adjusted(3,3,-3,-3) ;

    QColor penColor = 0x4B4B4B ;
    if(m_type == 0)
    {
        //painter.setPen(0x4B4B4B);
        penColor= 0x4B4B4B ;
        painter.setBrush(Qt::white) ;
    }

    if(m_type == 1)
    {
        painter.setPen(Qt::NoPen);
        painter.setBrush(Qt::NoBrush) ;
    }

    if(m_type == 2)
    {
        //painter.setPen(0x4B4B4B);
        painter.setBrush(0x4B4B4B) ;
    }

    QPen pen(penColor,0.5) ;
    pen.setCapStyle(Qt::FlatCap);
    if(m_type != 1) painter.setPen(pen);
    painter.drawRoundedRect(rect,16,16);

    if(m_type == 1) painter.setPen(0xFF9052);
    if(m_type == 2) painter.setPen(Qt::white);
    painter.setFont(this->font()) ;
    painter.drawText(rect,m_text,QTextOption(Qt::AlignCenter)) ;

    if(m_bSelected)
    {
        painter.setRenderHint(QPainter::Antialiasing,false) ;
        painter.setPen(QPen(Qt::blue,0.5,Qt::DashLine));
        painter.setBrush(Qt::NoBrush) ;
        painter.drawRect(this->rect().adjusted(1,1,-1,-1)) ;
        qDebug() << m_text;
    }

    event->accept() ;
}

bool MacroSquare::event(QEvent *event)
{
    if(event->type() == QEvent::MouseButtonRelease)
    {
        m_bSelected = !m_bSelected;
        update();
        return true;
    }
    return QWidget::event(event) ;
}
