#include "ModuleKeyboard.h"
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
                min-width:48px;
                min-height:48px;
                max-width:548px;
                max-height:48px; }

            QPushButton:hover { background-color: #87ceeb; border: 1px solid #AF00AF;}

            QPushButton:pressed { background-color: #3F3F3F; }
            QPushButton:checked { background-color: #3F3F3F; color:white; }
            QPushButton:disabled { background-color: #EAEAEA; color: #8C8C8C; }
        )");

    for(int i=0; i<150; i++)
    {
        QString strName = QString::asprintf("pushButton_%02d",i+1) ;
        QPushButton *btn = findChild<QPushButton*>(strName) ;
        if(btn)
        {
            btn->setStyleSheet(strStyle) ;
            btn->setCheckable(true) ;
            btn->setFocusPolicy(Qt::NoFocus);
            btn->setCursor(Qt::PointingHandCursor) ;
            ui->buttonGroup->addButton(btn,i) ;

            if(i==14)
            {
                btn->setEnabled(false) ;
                btn->setFixedSize(48,48) ;
                btn->setStyleSheet(R"(
                    QPushButton
                    {
                     border: 1px solid #EAEAEA;
                     border-radius: 24px;
                     max-width:48px;
                     max-height:48px;
                     min-width:48px;
                     min-height:48px;}

                    QPushButton:disabled { background-color: #EAEAEA; color: #8C8C8C; }
                )") ;
            }


            if(i==44)
                btn->setEnabled(false) ;
        }
    }
    ui->buttonGroup->setExclusive(false) ;
    connect(ui->buttonGroup,&QButtonGroup::idClicked,this,[=](int id){
        qDebug() << "Clicked:" << id ;
    });

    //setStyleSheet("QFrame { border-radius: 8px; border: 1px solid #FF00FF; }") ;
}

ModuleKeyboard::~ModuleKeyboard()
{
    delete ui;
}

void ModuleKeyboard::showFlag(bool show)
{
    ui->frameFlag->setVisible(show) ;
}

