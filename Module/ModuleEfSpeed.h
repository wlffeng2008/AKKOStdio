#ifndef MODULEEFSPEED_H
#define MODULEEFSPEED_H

#include <QFrame>

namespace Ui {
class ModuleEfSpeed;
}

class ModuleEfSpeed : public QFrame
{
    Q_OBJECT

public:
    explicit ModuleEfSpeed(QWidget *parent = nullptr);
    ~ModuleEfSpeed();

signals:
    void onSpeedChanged(int speed);

private:
    Ui::ModuleEfSpeed *ui;
};

#endif // MODULEEFSPEED_H
