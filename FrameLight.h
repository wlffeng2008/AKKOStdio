#ifndef FRAMELIGHT_H
#define FRAMELIGHT_H

#include <QFrame>

namespace Ui {
class FrameLight;
}

class FrameLight : public QFrame
{
    Q_OBJECT

public:
    explicit FrameLight(QWidget *parent = nullptr);
    ~FrameLight();

private:
    Ui::FrameLight *ui;
};

#endif // FRAMELIGHT_H
