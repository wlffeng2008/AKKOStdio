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
                    outline: none;
                    background-color: #FBFBFB;
                        min-width:42px;
                        max-width:542px;
                        min-height:42px;
                        font-size: 12px ;
                        font-weight: 500 ;
                        font-family: MiSans; }

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
            btn->setStyleSheet(strStyle) ;
            btn->setCheckable(true) ;
            btn->setFocusPolicy(Qt::NoFocus);
            btn->setCursor(Qt::PointingHandCursor) ;
            ui->buttonGroup->addButton(btn,nIndex++) ;

            if(i == 0xE000)
            {
                btn->setEnabled(false) ;
                btn->setFixedSize(48,48) ;
                btn->setStyleSheet(R"(
                    QPushButton {
                        border: 1px solid #EAEAEA;
                        border-radius: 24px;
                        padding: 2px 2px;
                        min-width:42px;
                        min-height:42px;
                        color: black;
                        background-color: #FFFFFF; }

                    QPushButton:checked { background-color: #3F3F3F; color: white; }
                    QPushButton:disabled { background-color: #EAEAEA; color: black; }
                )") ;
            }
         }
    }

    ui->buttonGroup->setExclusive(false) ;

    connect(ui->buttonGroup,&QButtonGroup::idClicked,this,[=](int id){

        const QList<QAbstractButton*>btns = ui->buttonGroup->buttons();
        int nChecked = 0;
        for(QAbstractButton*btn:btns)
        {
            if(nChecked >= 3)
            {
                btn->setChecked(false);
                continue ;
            }

            if(btn->isChecked())
                nChecked++ ;
        }

        QPushButton *btn = static_cast<QPushButton *>(ui->buttonGroup->button(id)) ;
        // qDebug() << "Clicked:" << id << btn->objectName() ;
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
    if(nCode == 0)
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
                background-color: #FF9052;
                color: black;
                min-width: 42px;
                min-height: 42px;
            }
            QPushButton:disabled { background-color: #FF9052; color: white; }
        )") ;

        if(btn->objectName() == "pushButton_E000")
        {
            btn->setStyleSheet(R"(
                QPushButton {
                    border: 1px solid #EAEAEA;
                    border-radius: 24px;
                    padding: 2px 2px;
                    min-width:42px;
                    min-height:42px; }

                QPushButton:disabled { background-color: #FF9052; color: white; }
            )") ;
        }
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
                min-width: 42px;
                min-height: 42px;
            }
            QPushButton:disabled { background-color: white; color: black; }
        )");

        if(btn->objectName() == "pushButton_E000")
        {
            btn->setStyleSheet(R"(
                QPushButton {
                    border: 1px solid #EAEAEA;
                    border-radius: 24px;
                    padding: 2px 2px;
                    min-width:42px;
                    min-height:42px; }

                QPushButton:disabled { background-color: white; color: black; }
            )") ;
        }
        btn->setEnabled(set) ;
    }
    ui->frameFlag->hide() ;
}

