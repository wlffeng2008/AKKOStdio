#ifndef FRAMEMACRO_H
#define FRAMEMACRO_H

#include <QFrame>

namespace Ui {
class FrameMacro;
}

class FrameMacro : public QFrame
{
    Q_OBJECT

public:
    explicit FrameMacro(QWidget *parent = nullptr);
    ~FrameMacro();

private:
    Ui::FrameMacro *ui;
};

#endif // FRAMEMACRO_H
