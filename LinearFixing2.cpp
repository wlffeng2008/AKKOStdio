#include "LinearFixing2.h"
#include "ModuleKeyboard.h"

#include <QScreen>
#include <QPainter>
#include <QKeyEvent>
#include <QStyleOption>
#include <QApplication>

static ModuleKeyboard *pKeyBoard = nullptr ;

LinearFixing2::LinearFixing2(const QString& title,const QString& content, QWidget *parent)
    : QDialog(parent)
{
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::MSWindowsFixedSizeDialogHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setModal(true);

    setStyleSheet("QDialog{background-color: rgba(0, 0, 0, 0.5);  border: 1px solid transparent;border-radius:12px;}"); // 黑色半透明

    QWidget* pContentWidget = new QWidget(this);
    pContentWidget->setStyleSheet(R"(
        QWidget {
            background-color: white;
            border-radius: 32px;
            padding: 10px;
        }
    )");

    QLabel *pLabTitle = new QLabel("请依次将每个按键轻按到底并停留至少1秒钟，直到按键变为橙色（表示该按键校准成功），请勿遗漏，可重复按按键。无线下不支持按键校准个数提示。校准过程中请勿拔出数据线。", pContentWidget);
    pLabTitle->setStyleSheet("font-size: 16px; color: #333; text-align: center;padding: 8px 145px;");
    pLabTitle->setWordWrap(true);
    pLabTitle->setAlignment(Qt::AlignCenter);

    pKeyBoard = new ModuleKeyboard(pContentWidget) ;
    pKeyBoard->setKeyCllickable(false) ;

    QPushButton* confirmBtn = new QPushButton("完成校准", pContentWidget);
    confirmBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #6329B6;
            color: white;
            min-width:102px;
            min-height:32px;
            max-width:102px;
            max-height:32px;
            border: none;
            border-radius: 12px;
            padding: 2px 2px;
            font-size: 14px;
        }
        QPushButton:hover { background-color: #0E42F2; }
        QPushButton:pressed { background-color: #0A34A1; }
    )");
    connect(confirmBtn, &QPushButton::clicked, this, &QDialog::accept);

    QPushButton* cancelBtn = new QPushButton("取消", pContentWidget);
    cancelBtn->setStyleSheet(R"(
        QPushButton {
            background-color: gray;
            color: white;
            min-width:102px;
            min-height:32px;
            padding: 2px 2px;
            border: none;
            border-radius: 12px;
            font-size: 14px;
        }
        QPushButton:hover { background-color: #C2C2C2; }
        QPushButton:pressed { background-color: #0A34A1; }
    )");
    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);

    cancelBtn->setFocusPolicy(Qt::NoFocus) ;
    cancelBtn->setCursor(Qt::PointingHandCursor) ;
    confirmBtn->setFocusPolicy(Qt::NoFocus) ;
    confirmBtn->setCursor(Qt::PointingHandCursor) ;

    // 内容布局
    QVBoxLayout* contentLayout = new QVBoxLayout(pContentWidget);
    contentLayout->addWidget(pLabTitle);
    contentLayout->addWidget(pKeyBoard,1);

    QHBoxLayout* btnLayout = new QHBoxLayout(pContentWidget) ;
    btnLayout->addWidget(cancelBtn, 0, Qt::AlignCenter);
    btnLayout->addWidget(confirmBtn, 0, Qt::AlignCenter);
    btnLayout->setAlignment(Qt::AlignHCenter);
    btnLayout->setSpacing(18) ;
    btnLayout->setContentsMargins(10,10,10,10) ;
    contentLayout->addItem(btnLayout) ;

    // 主布局
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(pContentWidget, 1, Qt::AlignCenter);

    pContentWidget->setFixedSize(1130,540);
    pContentWidget->adjustSize();
    QRect geoMetry = QApplication::primaryScreen()->geometry(); ;
    if(parent) geoMetry = parent->geometry() ;
    setFixedSize(geoMetry.width(), geoMetry.height());
}

void LinearFixing2::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    QDialog::paintEvent(event);
}

void LinearFixing2::keyPressEvent(QKeyEvent *event)
{
    //qDebug() << "LinearFixing2::keyPressEvent" << Qt::hex << event->key() << event->text()  << event->nativeVirtualKey() << event->nativeScanCode() ;
    qDebug() << QString::asprintf("pushButton_%04X",event->nativeScanCode());
    event->ignore() ;
    pKeyBoard->setkeyHited(event->nativeScanCode()) ;
    //pKeyBoard->setkeyHited(0) ;
}
