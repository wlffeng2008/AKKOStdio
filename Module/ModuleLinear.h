#ifndef MODULELINEAR_H
#define MODULELINEAR_H

#include <QFrame>

namespace Ui {
class ModuleLinear;
}

class ModuleLinear : public QFrame
{
    Q_OBJECT

public:
    explicit ModuleLinear(QWidget *parent = nullptr);
    ~ModuleLinear();

private:
    Ui::ModuleLinear *ui;
};

#endif // MODULELINEAR_H
