#ifndef FRAMEKEYSETTING_H
#define FRAMEKEYSETTING_H

#include <QFrame>

namespace Ui {
class FrameKeySetting;
}

class FrameKeySetting : public QFrame
{
    Q_OBJECT

public:
    explicit FrameKeySetting(QWidget *parent = nullptr);
    ~FrameKeySetting();

private:
    Ui::FrameKeySetting *ui;
};

#endif // FRAMEKEYSETTING_H
