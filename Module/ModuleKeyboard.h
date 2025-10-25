#ifndef MODULEKEYBOARD_H
#define MODULEKEYBOARD_H

#include <QAbstractButton>
#include <QFrame>

#include "SuperLabel.h"

namespace Ui {
class ModuleKeyboard;
}

class ModuleKeyboard : public QFrame
{
    Q_OBJECT

public:
    explicit ModuleKeyboard(QWidget *parent = nullptr);
    ~ModuleKeyboard();

    void setKeyFixMode() ;
    void setkeyHited(int id) ;
    void showFlag(bool show=true);
    void setKeyEnable(const QString&objname,bool bEnable,bool bSetToAll=false) ;

protected:
    void keyPressEvent(QKeyEvent *event) override;
    bool event(QEvent *event) override;
    bool eventFilter(QObject *watched,QEvent *event) override;

private:
    Ui::ModuleKeyboard *ui;

    QList<QAbstractButton*>m_disables ;
    QAbstractButton*m_curBtn = nullptr;
    QAbstractButton*m_spcBtn = nullptr;
    CustomTooltip *m_Menu = nullptr;

    bool m_bFixMode = false ;
};

#endif // MODULEKEYBOARD_H
