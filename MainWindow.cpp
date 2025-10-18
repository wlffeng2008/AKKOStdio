#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QEvent>
#include <QKeyEvent>
#include <QPainter>
#include <QDebug>
#include <QRadioButton>
#include <QSpacerItem>
#include <QButtonGroup>
#include <QGraphicsDropShadowEffect>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint|Qt::MSWindowsFixedSizeDialogHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setStyleSheet("QMainWindow{background-color: rgba(255, 255, 255, 0.8); border: 1px solid skyblue; border-radius: 12px; }");

    // QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    // shadowEffect->setBlurRadius(15);    // 阴影模糊半径，值越大越模糊
    // shadowEffect->setColor(QColor(0, 0, 0, 160)); // 阴影颜色和透明度 (RGBA)
    // shadowEffect->setOffset(0, 0);      // 阴影偏移量，设为(0,0)四周均匀
    // this->setGraphicsEffect(shadowEffect);
    // centralWidget()->setContentsMargins(10, 10, 10, 10);

    setWindowTitle(QString("AKKO Studio -- By QT") + QT_VERSION_STR);
    resize(1280,900) ;

    m_pDevice = new DialogDeviceConnect(this) ;
    m_pMainkwork = new DialogMainwork(this) ;
    connect(ui->pushButtonDevice,&QPushButton::clicked,this,[=]{
        m_pDevice->show() ;
    });

    connect(ui->pushButtonEnter,&QPushButton::clicked,this,[=]{
        m_pMainkwork->setGeometry(frameGeometry()) ;
        m_pMainkwork->show() ;
    });

    connect(ui->pushButtonExit,&QPushButton::clicked,this,[=]{
        close() ;
    });

    QList<QPushButton *>btns = findChildren<QPushButton *>();
    for(QPushButton *btn:std::as_const(btns))
    {
        btn->setCursor(Qt::PointingHandCursor);
        btn->setFocusPolicy(Qt::ClickFocus) ;
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    m_pDevice->disconnect() ;

    QCoreApplication::exit() ;
    QMainWindow::closeEvent(event);
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        close() ;
    }

    QMainWindow::keyReleaseEvent(event);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if(event->pos().y() < 50)
        {
            m_dragPosition = event->globalPos() - frameGeometry().topLeft();
            event->accept();
            m_dragging = true ;
            return ;
        }
    }
    QMainWindow::mousePressEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton && m_dragging) {
        move(event->globalPos() - m_dragPosition);
        event->accept();
    }
    // QMainWindow::mouseMoveEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_dragging = false;
        event->accept();
    }
    // QMainWindow::mouseReleaseEvent(event);
}


void MainWindow::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    QMainWindow::paintEvent(event);
}
