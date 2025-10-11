#ifndef MODULERTSET_H
#define MODULERTSET_H

#include <QFrame>

namespace Ui {
class ModuleRtSet;
}

class ModuleRtSet : public QFrame
{
    Q_OBJECT

public:
    explicit ModuleRtSet(QWidget *parent = nullptr);
    ~ModuleRtSet();

protected:
    void paintEvent(QPaintEvent *event) override;
    bool eventFilter(QObject*,QEvent*) override;

private:
    Ui::ModuleRtSet *ui;
    void setValue(float value);
    float getValue();
};

#endif // MODULERTSET_H
