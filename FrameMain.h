#ifndef FRAMEMAIN_H
#define FRAMEMAIN_H

#include <QFrame>
namespace Ui {
class FrameMain;
}

class FrameMain : public QFrame
{
    Q_OBJECT

public:
    explicit FrameMain(QWidget *parent = nullptr);
    ~FrameMain();

private:
    Ui::FrameMain *ui;
};

#endif // FRAMEMAIN_H
