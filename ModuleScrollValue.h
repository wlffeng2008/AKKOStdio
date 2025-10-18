#ifndef MODULESCROLLVALUE_H
#define MODULESCROLLVALUE_H

#include <QFrame>
#include <QEvent>

namespace Ui {
class ModuleScrollValue;
}

class ModuleScrollValue : public QFrame
{
    Q_OBJECT

public:
    explicit ModuleScrollValue(QWidget *parent = nullptr);
    ~ModuleScrollValue();
    void setValueList(QStringList&valus);

protected:
    bool event(QEvent*event) override;
    bool eventFilter(QObject*watched, QEvent*event) override;

private:
    Ui::ModuleScrollValue *ui;
    QStringList m_Values ;
    qint64 m_nIndex = 0;
    void rollValues();
};

#endif // MODULESCROLLVALUE_H
