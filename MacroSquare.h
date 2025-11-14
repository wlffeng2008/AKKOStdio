#ifndef MACROSQUARE_H
#define MACROSQUARE_H

#include <QWidget>
#include "SuperLabel.h"
#include <QSpinBox>

class MacroSquare : public QWidget
{
    Q_OBJECT
public:
    explicit MacroSquare(const QString&text, int type=0, QWidget *parent = nullptr);
    bool isSelected(){ return m_bSelected; }
    void setSelected(bool selected=true){ m_bSelected = selected; update(); }
    void closeItems();

    static void LostFocus() ;

protected:
    void paintEvent(QPaintEvent*event) override;
    bool event(QEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;

signals:

private:
    bool m_bSelected = false ;
    int  m_type = 0 ;
    QString m_text ;

    CustomTooltip *m_tTip=nullptr;
    CustomTooltip *m_rTip=nullptr;
    CustomTooltip *m_bTip=nullptr;
    QSpinBox *m_spin=nullptr;
};

#endif // MACROSQUARE_H
