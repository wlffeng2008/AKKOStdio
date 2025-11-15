#include "DialogMainwork.h"
#include "ui_DialogMainwork.h"
#include <QPainter>
#include <QGraphicsDropShadowEffect>

#include "FrameMain.h"
#include "FrameKeySetting.h"
#include "FrameMacro.h"
#include "FrameMagic.h"
#include "FrameLight.h"
#include "FrameAbout.h"
#include "ModuleLangMenu.h"
#include "LinearFixing1.h"
#include "ModuleGeneralMasker.h"
#include "ModuleLinear.h"
#include <QMenu>
#include <QAction>

DialogMainwork::DialogMainwork(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogMainwork)
{
    ui->setupUi(this);
    setFixedSize(1280,900) ;
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint|Qt::MSWindowsFixedSizeDialogHint|Qt::Desktop);
    setAttribute(Qt::WA_TranslucentBackground);
    setFocusPolicy(Qt::StrongFocus) ;

    ui->pushButtonPaire->hide();

    FrameKeySetting *pKS = new FrameKeySetting(this) ;
    FrameMain *pFM = new FrameMain(this) ;
    pKS->hide() ;
    FrameMagic *pMagic = new FrameMagic(this);
    FrameMacro *pMacro = new FrameMacro(this);
    FrameLight *pLight = new FrameLight(this);
    FrameAbout *pAbout = new FrameAbout(this);

    m_pFrames.push_back(pFM) ;
    m_pFrames.push_back(pKS) ;
    m_pFrames.push_back(pMagic) ;
    m_pFrames.push_back(pMacro) ;
    m_pFrames.push_back(pLight) ;
    m_pFrames.push_back(pAbout) ;

    ui->horizontalLayoutBR->addWidget(pFM);
    ui->horizontalLayoutBR->addWidget(pKS);
    ui->horizontalLayoutBR->addWidget(pMagic);
    ui->horizontalLayoutBR->addWidget(pMacro);
    ui->horizontalLayoutBR->addWidget(pLight);
    ui->horizontalLayoutBR->addWidget(pAbout);

    for(QFrame*frame:std::as_const(m_pFrames))
        frame->setFixedSize(1124,800) ;

    m_pLBtns.push_back(ui->label1);
    m_pLBtns.push_back(ui->label2);
    m_pLBtns.push_back(ui->label3);
    m_pLBtns.push_back(ui->label4);
    m_pLBtns.push_back(ui->label5);
    m_pLBtns.push_back(ui->label6);
    m_pLBtns.push_back(ui->label7);

    int index = 0 ;
    static QStringList images={"shouye","jianweishezhi","cizhoushezhi","hongshezhi","dengxiaoshezhi","guanyu","",""};
    foreach (SuperLabel *label, m_pLBtns) {
        label->setCursor(Qt::PointingHandCursor);
        label->installEventFilter(this) ;
        label->setAlignment(Qt::AlignCenter) ;
        label->setOwnSheet("QLabel { background-color: #6329B6; border-radius: 16px;}","QLabel { background-color: transparent; }") ;
        QString strImg = images[index++] + ".png";
        label->setImages(QString(":/images/leftbtns/1/") + strImg,QString(":/images/leftbtns/0/") + strImg) ;
    }
    clickLabel(ui->label1) ;

    m_pLBtns[6]->setImages(QString(":/images/User.png"),QString(":/images/User.png")) ;

    QString strStyle(R"(

        QPushButton {
            color: #333;
            margin-left:24px;
            border: none;
            font: 500 16px "MiSans";
            background: transparent;
            spacing:20px; }

        )") ;
    ui->pushButtonLang->setStyleSheet(strStyle);
    ui->pushButtonFixed->setStyleSheet(strStyle);
    ui->pushButtonReset->setStyleSheet(strStyle);
    ui->pushButtonPaire->setStyleSheet(strStyle);

    m_pLangMenu = new ModuleLangMenu(this) ;
    connect(m_pLangMenu,&ModuleLangMenu::onLangChanged,this,[=](int langId,const QString&lang){
        ui->pushButtonLang->setText(QString(" ")+lang) ;
    }) ;

    connect(ui->pushButtonLang,&QPushButton::clicked,this,[=]{
        ModuleLangMenu *pLangMenu = m_pLangMenu ;
        if(!pLangMenu->isHidden())
           return ;

        pLangMenu->setParent(nullptr) ;
        QRect btnRect = ui->pushButtonLang->geometry() ;
        QPoint PT = mapToGlobal(btnRect.bottomLeft());
        pLangMenu->setGeometry(PT.x() + 25,PT.y(),110,250);
        pLangMenu->setWindowFlags(Qt::FramelessWindowHint |Qt::WindowStaysOnTopHint|Qt::Tool|Qt::Dialog|Qt::Popup);
        pLangMenu->show() ;
    });

    connect(ui->pushButtonFixed,&QPushButton::clicked,this,[=]{
        LinearFixing1 T("","",this) ;
        T.exec() ;
    });

    connect(ui->pushButtonPaire,&QPushButton::clicked,this,[=]{

        ModuleLinear *pTest = new ModuleLinear(this) ;
        pTest->setObjectName("TestLinear");
        pTest->layout()->setContentsMargins(20,20,20,20) ;
        pTest->setStyleSheet("QFrame#TestLinear{background-color:white;min-height:320px; border-radius:24px;}") ;
        ModuleGeneralMasker T(pTest ,this) ;
        T.exec() ;
    });
}

DialogMainwork::~DialogMainwork()
{
    delete ui;
}

void DialogMainwork::clickLabel(QLabel *label, int index)
{
    if(index == 6)
    {
        hide() ;
        return ;
    }

    ((SuperLabel *)label)->setFocus();

    for(int i=0; i<m_pFrames.count(); i++)
    {
        QFrame *pFM = m_pFrames[i];
        if(pFM)
        {
            if(index == i)
                pFM->show();
            else
                pFM->hide();
        }
    }
}

bool DialogMainwork::eventFilter(QObject *watch, QEvent *event)
{
    //qDebug() << event->type() ;
    if(event->type() == QEvent::MouseButtonRelease)
    {
        int nCount = m_pLBtns.count() ;
        for(int i=0; i<nCount; i++)
        {
            if(m_pLBtns[i] == watch)
            {
                QLabel* label = qobject_cast<QLabel*>(watch);
                clickLabel(label,i) ;
                return true ;
            }
        }
    }
    if(event->type() == QEvent::Paint || event->type() == QEvent::WindowDeactivate || event->type() == QEvent::WindowActivate)
    {
        m_pLangMenu->hide() ;
    }

    return QDialog::eventFilter(watch, event);
}

void DialogMainwork::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QRect rect = this->rect();
    painter.setBrush(QBrush(Qt::white));
    painter.setPen(QPen(QColor(200, 200, 200), 1));
    painter.drawRoundedRect(rect, 12, 12);

    event->accept() ;
}

void DialogMainwork::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if(m_pLangMenu) m_pLangMenu->hide() ;
        if(event->pos().y() < 50)
        {
            m_dragPosition = event->globalPos() - frameGeometry().topLeft();
            event->accept();
            m_dragging = true ;
            return ;
        }
    }
    QDialog::mousePressEvent(event);
}

void DialogMainwork::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton && m_dragging) {
        move(event->globalPos() - m_dragPosition);
        event->accept();
    }
    // QDialog::mouseMoveEvent(event);
}

void DialogMainwork::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_dragging = false;
        event->accept();
    }
    // QDialog::mouseReleaseEvent(event);
}


void DialogMainwork::focusOutEvent(QFocusEvent *event)
{
    if(m_pLangMenu) m_pLangMenu->hide() ;
}

void DialogMainwork::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "DialogMainwork::QKeyEvent" << event->key() << event->nativeScanCode() ;
}

void DialogMainwork::keyReleaseEvent(QKeyEvent *event)
{

}

