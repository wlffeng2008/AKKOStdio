#ifndef MACROITEM_H
#define MACROITEM_H

#include <QFrame>

namespace Ui {
class MacroItem;
}

class MacroItem : public QFrame
{
    Q_OBJECT

public:
    explicit MacroItem(QWidget *parent = nullptr);
    ~MacroItem();

protected:
    bool event(QEvent *event) override;

signals:
    void onOperation(int operation,QWidget *from);

private:
    Ui::MacroItem *ui;
};

#endif // MACROITEM_H
