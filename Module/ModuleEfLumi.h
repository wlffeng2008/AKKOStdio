#ifndef MODULEEFLUMI_H
#define MODULEEFLUMI_H

#include <QFrame>

namespace Ui {
class ModuleEfLumi;
}

class ModuleEfLumi : public QFrame
{
    Q_OBJECT

public:
    explicit ModuleEfLumi(QWidget *parent = nullptr);
    ~ModuleEfLumi();

private:
    Ui::ModuleEfLumi *ui;
};

#endif // MODULEEFLUMI_H
