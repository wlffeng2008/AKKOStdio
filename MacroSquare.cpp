#include "MacroSquare.h"

#include <QPainter>
#include <QEvent>
#include <QPaintEvent>
#include <QMouseEvent>

static MacroSquare *s_pCurItem = nullptr ;
static QString s_strTipBtnStyle(R"(
    background-color: white;
    border: 1px solid #DEDEDE;
    border-radius: 4px;
    padding-left: 5px;
    padding-right: 5px;
    min-height:24px;
    max-height:24px;
    font-size: 14px;
    font-weight:400;
)");

MacroSquare::MacroSquare(const QString &text, int type, QWidget *parent)
    : QWidget{parent}
{
    setCursor(Qt::PointingHandCursor) ;
    setFocusPolicy(Qt::StrongFocus) ;
    // qDebug() << parent;

    m_type = type;
    m_text = text;

    m_tTip=new CustomTooltip(this);
    m_rTip=new CustomTooltip(this);
    m_bTip=new CustomTooltip(this);

    m_tTip->setAutohide(false);
    m_rTip->setAutohide(false);
    m_bTip->setAutohide(false);

    m_tTip->setStyleSheet(s_strTipBtnStyle);
    m_rTip->setStyleSheet(s_strTipBtnStyle);
    m_bTip->setStyleSheet(s_strTipBtnStyle);

    m_tTip->setText(tr("添加"));
    m_rTip->setText(tr("修改"));
    m_bTip->setText(tr("删除"));

    connect(m_tTip,&CustomTooltip::onClicked,this,[=]{
        m_tTip->hide();
        m_rTip->hide();
        m_bTip->hide();
    });

    connect(m_rTip,&CustomTooltip::onClicked,this,[=]{
        m_tTip->hide();
        m_rTip->hide();
        m_bTip->hide();
    });

    connect(m_bTip,&CustomTooltip::onClicked,this,[=]{
        m_tTip->hide();
        m_rTip->hide();
        m_bTip->hide();
    });

    if(type == 1)
    {
        m_text = QString::number(rand()%500);
        m_spin = new QSpinBox(this);
        m_spin->setRange(5,10000);
        m_spin->hide() ;
        m_spin->setAlignment(Qt::AlignCenter);
        m_spin->setGeometry(QRect(0,12,48,24));
        m_spin->installEventFilter(this);
        connect(m_spin,&QSpinBox::valueChanged,this,[=](int value){
            m_text=QString::number(value);
        });
    }

    m_tTip->installEventFilter(this);
}

void MacroSquare::closeItems()
{
    if(m_spin) m_spin->hide();

    if(m_tTip)
    {
        m_tTip->hide();
        m_rTip->hide();
        m_bTip->hide();
    }
}

void MacroSquare::LostFocus()
{
    if(s_pCurItem) s_pCurItem->closeItems() ;
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
        if(m_spin->isHidden())
        {
            painter.setPen(QPen(QBrush(0xFF9052),0.5));
            painter.setBrush(Qt::NoBrush) ;
            int nCY = rect.center().y() ;
            int nHY = rect.height() ;
            painter.drawLine(QPoint(rect.left(),nCY),QPoint(rect.right(),nCY));

            painter.drawLine(QPoint(rect.right()-8,nCY+3),QPoint(rect.right(),nCY));
            painter.drawLine(QPoint(rect.right()-8,nCY-3),QPoint(rect.right(),nCY));

            painter.setPen(Qt::black);
            painter.drawText(rect.adjusted(0,0,0,-nHY/2),m_text,QTextOption(Qt::AlignCenter)) ;
            painter.drawText(rect.adjusted(0,nHY/2-5,0,0),"ms",QTextOption(Qt::AlignCenter)) ;
        }
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
    }

    if(s_pCurItem != this) closeItems();

    event->accept() ;
}

bool MacroSquare::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this)
    {
        qDebug() << event->type() ;
    }

    if (event->type() == QEvent::FocusOut) {
        closeItems() ;
    }

    return QWidget::eventFilter(watched, event);
}

bool MacroSquare::event(QEvent *event)
{
    if(event->type() == QEvent::FocusOut)
    {
        closeItems();
    }

    if(event->type() == QEvent::MouseButtonPress)
    {
        MacroSquare *old = s_pCurItem ;
        s_pCurItem = this ;
        if(old) old->update();

        m_bSelected = !m_bSelected;
    //     update();
    //     return true;
    // }

    // if(event->type() == QEvent::MouseButtonRelease)
    // {
        if(m_type == 1)
        {
            if(m_spin->isHidden())
            {
                m_spin->setValue(m_text.toInt()) ;
                m_spin->show() ;
                m_spin->setFocus() ;
            }
            else
            {
                m_spin->hide() ;
            }
        }
        else
        {
            if(m_tTip->isHidden())
            {
                if(m_bSelected)
                {
                    QPoint pos = mapToGlobal(QPoint(width()+1,(height() - m_rTip->height())/2));
                    m_rTip->move(pos);

                    pos = mapToGlobal(QPoint(size().width()/2 - m_tTip->width()/2,( -1 - m_tTip->height())));
                    m_tTip->move(pos);

                    pos = mapToGlobal(QPoint(size().width()/2 - m_bTip->width()/2,(height() + 1)));
                    m_bTip->move(pos);

                    m_rTip->show();
                    m_tTip->show();
                    m_bTip->show();
                    m_tTip->setFocus();
                }
            }
            else
            {
                closeItems();
            }
        }
        update() ;
        return true;
    }
    return QWidget::event(event) ;
}
