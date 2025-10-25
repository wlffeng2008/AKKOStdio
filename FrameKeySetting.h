#ifndef FRAMEKEYSETTING_H
#define FRAMEKEYSETTING_H

#include <QFrame>
#include "ModuleDKSAdjust.h"
#include "ModuleDKSAdjust.h"
#include <QLabel>

namespace Ui {
class FrameKeySetting;
}

class FrameKeySetting : public QFrame
{
    Q_OBJECT

public:
    explicit FrameKeySetting(QWidget *parent = nullptr);
    ~FrameKeySetting();
protected:
    bool eventFilter(QObject*watched,QEvent*event) override;
private:
    Ui::FrameKeySetting *ui;
    ModuleDKSAdjust *m_adjust = nullptr ;
    QLabel *m_toAdjust = nullptr ;
};

#endif // FRAMEKEYSETTING_H
