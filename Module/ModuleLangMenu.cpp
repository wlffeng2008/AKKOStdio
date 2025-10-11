#include "ModuleLangMenu.h"
#include "ui_ModuleLangMenu.h"
#include <QFocusEvent>
#include <QButtonGroup>
#include <QPushButton>
#include <QPainter>
#include <QStyleOption>
#include <QTimer>

ModuleLangMenu::ModuleLangMenu(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ModuleLangMenu)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint|Qt::MSWindowsFixedSizeDialogHint);
    setAttribute(Qt::WA_TranslucentBackground);
    //setFocusPolicy(Qt::StrongFocus);
    //setFixedSize(100,250) ;

    static QStringList Langs={tr("中文简体"),tr("English"),tr("한국어"),tr("日本語"),tr("Русский"),tr("Tiếng Việt"),tr("Português")} ;

    QString strStyle(R"(

            QPushButton {
                width: 86px;
                height: 24px;
                border-radius: 10px ;
                font-size: 12px ;
                font-weight: normal ;
                font-family: MiSans;

                color: #333;
                border: 1px soild white;
                background: white; }

            QPushButton:hover {
                border: 1px soild #F0F0F0;
                background: #F0F0F0; }

            QPushButton:checked {
                color: white;
                border: 1px soild #6329B6;
                background: #6329B6; }
            )") ;
    m_pBtnGrp = new QButtonGroup(this) ;
    QLayout *pLayout = ui->verticalLayout ;
    pLayout->setSpacing(6) ;
    pLayout->setAlignment(Qt::AlignTop|Qt::AlignHCenter) ;
    pLayout->setContentsMargins(3,3,3,3);

    connect(m_pBtnGrp,&QButtonGroup::idClicked,this,[=](int id){
        qDebug() << "Language QButtonGroup:" << id  << Langs[id];
        hide() ;
        emit onLangChanged(id,Langs[id]) ;
    });

    for(int i=0; i<Langs.count(); i++)
    {
        QPushButton *btn = new QPushButton(Langs[i],this) ;
        btn->setFixedSize(90,24);
        btn->setCheckable(true) ;
        btn->setStyleSheet(strStyle);
        //btn->setFocusPolicy(Qt::NoFocus) ;
        btn->setCursor(Qt::PointingHandCursor) ;

        m_pBtnGrp->addButton(btn,i);
        pLayout->addWidget(btn);
    }

    QTimer::singleShot(100,this,[=]{ m_pBtnGrp->button(0)->click(); });

    setFocusPolicy(Qt::StrongFocus);
    setStyleSheet("QDialog{background-color: rgba(255, 255, 255, 1); border: 1px solid #EAEAEA; border-radius:12px;}");
}

ModuleLangMenu::~ModuleLangMenu()
{
    delete ui;
}

void ModuleLangMenu::setLanguage(int langId)
{
    if(langId>6)
        return ;

    m_pBtnGrp->button(langId)->click() ;
}

void ModuleLangMenu::focusOutEvent(QFocusEvent *event)
{
    QDialog::focusOutEvent(event);
    this->hide() ;
}

void ModuleLangMenu::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    QDialog::paintEvent(event);
}
