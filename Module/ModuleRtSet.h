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

private:
    Ui::ModuleRtSet *ui;
};

#endif // MODULERTSET_H
