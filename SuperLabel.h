#ifndef SUPERLABEL_H
#define SUPERLABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QDebug>


class CustomTooltip : public QWidget {
public:
    CustomTooltip(QWidget *parent = nullptr) : QWidget(parent)
    {
        setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint);
        setAttribute(Qt::WA_TranslucentBackground);
        setStyleSheet("background-color: white; border: 1px solid #DEDEDE; border-radius: 16px; font-size:16px; padding-left: 16px; padding-right: 16px;min-height:42px; max-height:42px;");

        content = new QLabel(this);
        content->setAlignment(Qt::AlignCenter);
    }
    void setText(const QString&strText){ content->setText(strText); content->update(); show(); hide() ;} ;

private:
    QLabel *content = nullptr;
};


class SuperLabel : public QLabel
{
    Q_OBJECT
public:
    explicit SuperLabel(QWidget *parent = nullptr);

    void setImages(const QString&strGetfocus,const QString&strLostfocus) ;
    void setOwnSheet(const QString&strGetfocus,const QString&strLostfocus) ;
    void setFocus(bool foucs=true) ;
    bool getFoucus(){ return m_bFoucs ; };
protected:
    bool event(QEvent *event) override;

signals:

private:
    CustomTooltip *tooltip;
    QTimer *timer;
    bool m_bFoucs = false ;
    bool m_bEmpty = false ;
    QString m_strGetfocus ;
    QString m_strLostfocus ;
    QString m_strSheetGetfocus ;
    QString m_strSheetLostfocus ;
};

#endif // SUPERLABEL_H
