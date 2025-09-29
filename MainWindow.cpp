#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QKeyEvent>
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
    //setAttribute(Qt::WA_TranslucentBackground);

    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(15);    // 阴影模糊半径，值越大越模糊
    shadowEffect->setColor(QColor(0, 0, 0, 160)); // 阴影颜色和透明度 (RGBA)
    shadowEffect->setOffset(0, 0);      // 阴影偏移量，设为(0,0)四周均匀
    //this->setGraphicsEffect(shadowEffect);
    //centralWidget()->setContentsMargins(10, 10, 10, 10);

    setWindowTitle(QString("AKKO Studio -- By QT")+QT_VERSION_STR);
    resize(1280,900) ;

    m_pDevice = new DialogDeviceConnect(this) ;
    m_pMainkwork = new DialogMainwork(this) ;


    connect(ui->pushButtonDevice,&QPushButton::clicked,this,[=]{
        m_pDevice->show() ;
    });
    connect(ui->pushButtonEnter,&QPushButton::clicked,this,[=]{
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

    // QButtonGroup *pBtnGroup0 = new QButtonGroup(this) ;
    // for(int i=0; i<10; i++)
    // {
    //     QRadioButton *pBtn = new QRadioButton("选项" + QString::number(i));
    //     ui->horizontalLayout1->addWidget(pBtn) ;
    //     pBtnGroup0->addButton(pBtn,i);
    // }

    // connect(pBtnGroup0,&QButtonGroup::idClicked,this,[=](int id){
    //     qDebug() << id << pBtnGroup0->button(id)->text();
    // });

    // QSpacerItem *pHSp1 = new QSpacerItem(0,20,QSizePolicy::Expanding, QSizePolicy::Fixed);
    // QSpacerItem *pHSp2 = new QSpacerItem(0,20,QSizePolicy::Expanding, QSizePolicy::Fixed);

    // ui->horizontalLayout1->addItem(pHSp1);
    // ui->horizontalLayout2->addItem(pHSp2) ;

    // for(int i=0; i<10; i++)
    // {
    //     QRadioButton *pBtn = new QRadioButton("答案" + QString::number(i));
    //     ui->horizontalLayout2->addWidget(pBtn) ;
    // }
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
