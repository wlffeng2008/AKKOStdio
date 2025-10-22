#include "MacroSquare.h"

#include <QPainter>
#include <QEvent>
#include <QPaintEvent>
#include <QMouseEvent>

static MacroSquare *s_pCurItem = nullptr ;

MacroSquare::MacroSquare(const QString &text, int type, QWidget *parent)
    : QWidget{parent}
{
    setCursor(Qt::PointingHandCursor) ;
    m_type = type;
    m_text = text;
}

static QPointF drawArrowA(QPainter &painter, QPointF at,double w, double h, double rotate) {

    int nxp = at.x() ;
    int nyp = at.y() ;

    QPointF p0 =  QPointF(nxp + sin( rotate         ) * h, nyp - cos(rotate) * h        );
    QPointF p1 =  QPointF(nxp + sin( rotate + M_PI/2) * w, nyp - cos(rotate+ M_PI/2) * w);
    QPointF p2 =  QPointF(nxp + sin( rotate - M_PI/2) * w, nyp - cos(rotate- M_PI/2) * w);
    painter.drawPolygon(QPolygonF() << p0 << p1 << p2);

    return p0 ;
}

void MacroSquare::paintEvent(QPaintEvent*event)
{
    QPainter painter(this) ;
    painter.setRenderHint(QPainter::Antialiasing) ;
    QRect rect = this->rect().adjusted(3,3,-3,-3) ;

    if(m_type == 1)
    {
        painter.setPen(QPen(QBrush(0xFF9052),0.5));
        painter.setBrush(Qt::NoBrush) ;
        int nCY = rect.center().y() ;
        int nHY = rect.height() ;
        painter.drawLine(QPoint(rect.left(),nCY),QPoint(rect.right(),nCY));

        painter.drawLine(QPoint(rect.right()-8,nCY+3),QPoint(rect.right(),nCY));
        painter.drawLine(QPoint(rect.right()-8,nCY-3),QPoint(rect.right(),nCY));

        painter.setPen(Qt::black);
        painter.drawText(rect.adjusted(0,0,0,-nHY/2),"30",QTextOption(Qt::AlignCenter)) ;
        painter.drawText(rect.adjusted(0,nHY/2-5,0,0),"ms",QTextOption(Qt::AlignCenter)) ;
    }
    else
    {
        QColor penColor = 0x4B4B4B ;
        if(m_type == 0)
        {
            painter.setBrush(Qt::white) ;
        }
        if(m_type == 2)
        {
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
    }


    if(m_bSelected)
    {
        painter.setRenderHint(QPainter::Antialiasing,false) ;
        painter.setPen(QPen(s_pCurItem == this ? Qt::green : Qt::blue, 0.5, Qt::DashLine));
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
        if(s_pCurItem)
        {
            s_pCurItem->update();
        }
        s_pCurItem = this ;

        m_bSelected = !m_bSelected;
        update();
        return true;
    }
    return QWidget::event(event) ;
}
