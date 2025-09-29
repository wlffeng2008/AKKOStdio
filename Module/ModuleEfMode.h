#ifndef MODULEEFMODE_H
#define MODULEEFMODE_H

#include <QFrame>

namespace Ui {
class ModuleEfMode;
}

class ModuleEfMode: public QFrame
{
    Q_OBJECT

public:
    explicit ModuleEfMode(QWidget *parent = nullptr);
    ~ModuleEfMode();

private:
    Ui::ModuleEfMode *ui;
};

#endif // MODULEEFMODE_H
