#ifndef TOGGLEBUTTON_H
#define TOGGLEBUTTON_H

#include <QObject>
#include <QPushButton>
#include <QCheckBox>
#include <QWidget>
#include <QStyle>
#include <QTimer>
#include <QPaintEvent>
#include <QPainter>

class ToggleButton : public QCheckBox
{
    Q_OBJECT

public:
    ToggleButton(QWidget *parent = nullptr) : QCheckBox(parent)
    {
        setAttribute(Qt::WA_TranslucentBackground);
        setStyleSheet(R"(
            QCheckBox {
                min-width: 40px;
                height: 24px;}
        )");
    }

    bool getChecked(){ return m_bchecked; }

protected:
    bool event(QEvent *event) override
    {
        if(event->type() == QEvent::MouseButtonRelease)
        {
            m_bchecked = !m_bchecked ;
            update() ;
            emit clicked(m_bchecked) ;
            return true ;
        }
        return QCheckBox::event(event) ;
    }

    void paintEvent(QPaintEvent *event) override
    {
        QPainter painter(this) ;
        painter.setRenderHint(QPainter::Antialiasing);

        float nH = rect().height() ;
        if(m_bchecked)
        {
            painter.setPen(QPen(QColor(0x6329B6)));
            painter.setBrush(QBrush(QColor(0x6329B6)));
        }
        else
        {
            painter.setPen(QPen(Qt::gray));
            painter.setBrush(QBrush(Qt::gray));
        }
        painter.drawRoundedRect(rect(),nH/2,nH/2) ;

        int nRadius = nH/2 - 2 ;
        QRect rc = rect().adjusted(2,2,-2,-2) ;
        if(m_bchecked)
        {
            rc.setLeft(rc.right() - nRadius*2) ;
        }
        else
        {
            rc.setRight(rc.left() + nRadius*2) ;
        }

        painter.setPen(QPen(Qt::white));
        painter.setBrush(QBrush(Qt::white));
        painter.drawRoundedRect(rc,nRadius,nRadius) ;

        event->accept();
    }

private:
    bool m_bchecked=false ;
};

#endif // TOGGLEBUTTON_H
