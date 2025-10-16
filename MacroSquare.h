#ifndef MACROSQUARE_H
#define MACROSQUARE_H

#include <QWidget>

class MacroSquare : public QWidget
{
    Q_OBJECT
public:
    explicit MacroSquare(const QString&text, int type=0, QWidget *parent = nullptr);
    bool isSelected(){ return m_bSelected; }
    void setSelected(bool selected=true){ m_bSelected = selected; update(); }

protected:
    void paintEvent(QPaintEvent*event) override;
    bool event(QEvent *event) override;

signals:

private:
    bool m_bSelected = false ;
    int  m_type = 0 ;
    QString m_text ;
};

#endif // MACROSQUARE_H
