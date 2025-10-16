#include "ModuleKeyboard.h"
#include "qdialog.h"
#include "qstyle.h"
#include "ui_ModuleKeyboard.h"

#include <QPaintEvent>
#include <QPainter>
#include <QTimer>

ModuleKeyboard::ModuleKeyboard(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::ModuleKeyboard)
{
    ui->setupUi(this);
    QString strStyle(R"(

        QPushButton {
            border: 1px solid #EAEAEA;
            border-radius: 14px;
            padding: 2px 2px;
            color: black;
            background-color: #FFFFFF;
                min-width:46px;
                min-height:46px; }

            QPushButton:hover { background-color: #EAEAEA; border: 1px solid #EAEAEA;}

            QPushButton:pressed { background-color: #3F3F3F; }
            QPushButton:checked { background-color: #3F3F3F; color: white; }
            QPushButton:disabled { background-color: #EAEAEA; color: #8C8C8C; }
        )");

    //setStyleSheet(strStyle) ;
    int nIndex = 0 ;
    for(int i=0; i<0xFFFF; i++)
    {
        QString strName = QString::asprintf("pushButton_%04X",i) ;
        QPushButton *btn = findChild<QPushButton*>(strName) ;
        if(btn)
        {
            //qDebug() << btn->text() << i ;
            btn->setStyleSheet(strStyle) ;
            btn->setCheckable(true) ;
            btn->setFocusPolicy(Qt::NoFocus);
            btn->setCursor(Qt::PointingHandCursor) ;
            ui->buttonGroup->addButton(btn,nIndex++) ;

            if(nIndex==1400)
            {
                btn->setEnabled(false) ;
                btn->setFixedSize(48,48) ;
                btn->setStyleSheet(R"(
                    QPushButton {
                        border: 1px solid #EAEAEA;
                        border-radius: 24px;
                        padding: 2px 2px;
                        min-width:46px;
                        min-height:46px; }

                    QPushButton:disabled { background-color: #EAEAEA; color: #8C8C8C; }
                )") ;
            }
         }
    }
    ui->buttonGroup->setExclusive(false) ;
    connect(ui->buttonGroup,&QButtonGroup::idClicked,this,[=](int id){
        QPushButton *btn = static_cast<QPushButton *>(ui->buttonGroup->button(id)) ;
        qDebug() << "Clicked:" << id << btn->objectName() ;
    });
}

ModuleKeyboard::~ModuleKeyboard()
{
    delete ui;
}

void ModuleKeyboard::showFlag(bool show)
{
    ui->frameFlag->setVisible(show) ;
}

void ModuleKeyboard::keyPressEvent(QKeyEvent *event)
{
    QFrame::keyPressEvent(event) ;
}

void ModuleKeyboard::setkeyHited(int id)
{
    int nCode = id ;
    if(nCode == 0 || nCode == 0xE000)
        nCode = 0x81 ;

    QString strName = QString::asprintf("pushButton_%04X",nCode) ;
    QPushButton *btn = findChild<QPushButton*>(strName) ;
    if(btn)
    {
        btn->setStyleSheet(R"(
            QPushButton {
                border: 1px solid #EAEAEA;
                border-radius: 14px;
                padding: 2px 2px;
                background-color: yellow;
                color: black;
                min-width: 46px;
                min-height: 46px;
            }
            QPushButton:disabled { background-color: yellow; color: black; }
        )") ;
    }
}

void ModuleKeyboard::setKeyCllickable(bool set)
{
    const QList<QAbstractButton*>btns = ui->buttonGroup->buttons() ;
    for(QAbstractButton*btn:btns)
    {
        btn->setCheckable(set) ;
        btn->setStyleSheet(R"(
            QPushButton {
                border: 1px solid #EAEAEA;
                border-radius: 14px;
                padding: 2px 2px;
                background-color: white;
                color: black;
                min-width: 46px;
                min-height: 46px;
            }
            QPushButton:disabled { background-color: white; color: black; }
        )");
        btn->setEnabled(set) ;
    }
    ui->frameFlag->hide() ;
}

