#ifndef MODULEDKSITEM_H
#define MODULEDKSITEM_H

#include <QTimer>
#include <QFrame>

namespace Ui {
class ModuleDKSItem;
}

class ModuleDKSItem : public QFrame
{
    Q_OBJECT

public:
    explicit ModuleDKSItem(QWidget *parent = nullptr);
    ~ModuleDKSItem();

protected:
    bool eventFilter(QObject*watched, QEvent*event) override;
    bool event(QEvent*event) override;
    void paintEvent(QPaintEvent*event) override;

private:
    Ui::ModuleDKSItem *ui;

    bool m_dragging = false ;
    bool m_switchs[4]={false} ;
    int m_dragX1 = 0 ;
    int m_dragX2 = 0 ;
    QTimer m_TMReset ;
};

#endif // MODULEDKSITEM_H
