#ifndef MODULEKEYBOARD_H
#define MODULEKEYBOARD_H

#include <QFrame>

namespace Ui {
class ModuleKeyboard;
}

class ModuleKeyboard : public QFrame
{
    Q_OBJECT

public:
    explicit ModuleKeyboard(QWidget *parent = nullptr);
    ~ModuleKeyboard();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::ModuleKeyboard *ui;
};

#endif // MODULEKEYBOARD_H
