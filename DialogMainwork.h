#ifndef DIALOGMAINWORK_H
#define DIALOGMAINWORK_H

#include <QDialog>
#include <QLabel>
#include <QTimer>
#include <QPaintEvent>
#include "SuperLabel.h"
#include "ModuleLangMenu.h"

namespace Ui {
class DialogMainwork;
}



class DialogMainwork : public QDialog
{
    Q_OBJECT

public:
    explicit DialogMainwork(QWidget *parent = nullptr);
    ~DialogMainwork();

protected:
    bool eventFilter(QObject *watch, QEvent *event) override;
    void paintEvent(QPaintEvent *event) override ;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    Ui::DialogMainwork *ui;
    QPoint m_dragPosition;
    bool m_dragging = false;

    QList<SuperLabel *>m_pLBtns ;
    QList<QFrame *>m_pFrames ;
    void clickLabel(QLabel *label,int index=0);

    ModuleLangMenu *m_pLangMenu = nullptr ;
};

#endif // DIALOGMAINWORK_H
