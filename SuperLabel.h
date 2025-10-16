#ifndef SUPERLABEL_H
#define SUPERLABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QDebug>

class CustomTooltip : public QWidget
{
    Q_OBJECT
public:
    explicit CustomTooltip(QWidget *parent = nullptr);
    void setText(const QString&strText);

    static void setDefTipStyle(const QString& stryle) ;
    static void setGroupTipStyle( QObject *parent, QString&style) ;

private:
    QLabel *content = nullptr;
};

class SuperLabel : public QLabel
{
    Q_OBJECT
public:
    explicit SuperLabel(QWidget *parent = nullptr);

    void setImages(const QString&strGetfocus,const QString&strLostfocus);
    void setOwnSheet(const QString&strGetfocus,const QString&strLostfocus);
    void setFocus(bool foucs = true) ;
    bool getFoucus(){ return m_bFoucs; }
    CustomTooltip *getToolTip(){ return tooltip; }
    static void setGroupTipStyle(QObject *parent, QString &style) ;

protected:
    bool event(QEvent *event) override;

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
