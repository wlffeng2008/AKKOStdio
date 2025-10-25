#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

#include "DialogDeviceConnect.h"
#include "DialogMainwork.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override ;
    bool eventFilter(QObject *watched, QEvent *event) override ;
    void keyReleaseEvent(QKeyEvent *event) override ;
    void closeEvent(QCloseEvent *event) override ;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;
private:
    Ui::MainWindow *ui;
    QPoint m_dragPosition;
    bool m_dragging = false;

    DialogDeviceConnect *m_pDevice = nullptr ;
    DialogMainwork *m_pMainkwork = nullptr ;

};
#endif // MAINWINDOW_H
