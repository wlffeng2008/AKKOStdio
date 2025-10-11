#include "FrameKeySetting.h"
#include "ui_FrameKeySetting.h"

#include <QButtonGroup>

FrameKeySetting::FrameKeySetting(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::FrameKeySetting)
{
    ui->setupUi(this);

    {
        QString strStyle(R"(

            QPushButton {
                width: 120px;
                height: 32px;
                border-radius: 16px ;
                font-size: 16px ;
                font-weight: normal ;
                font-family: MiSans;


                color: #333;
                border: 1px soild #ECECEC;
                background: #FFFFFF; }

            QPushButton:checked {
                color: white;
                border: 1px soild #6329B6;
                background: #6329B6; }
            )") ;

        QLayout *pLayout = ui->frameMode->layout() ;
        pLayout->setSpacing(12) ;
        pLayout->setAlignment(Qt::AlignTop|Qt::AlignHCenter) ;

        QList<QPushButton *>btns = {ui->pushButtonSet1,ui->pushButtonSet2,ui->pushButtonSet3,ui->pushButtonSet4} ;
        QButtonGroup *pBtnGrp = new QButtonGroup(this) ;
        for(int i=0; i<btns.count(); i++)
        {
            QPushButton *btn = btns[i] ;
            btn->setFixedSize(120,24);
            btn->setCheckable(true) ;
            btn->setStyleSheet(strStyle);
            btn->setFocusPolicy(Qt::NoFocus) ;
            btn->setCursor(Qt::PointingHandCursor) ;
            pBtnGrp->addButton(btn,i);
        }
        connect(pBtnGrp,&QButtonGroup::idClicked,this,[=](int id){
            qDebug() << "Effect QButtonGroup:" << id ;
        });
        ui->pushButtonSet1->click() ;
    }

    {
        QString strStyle(R"(

        QPushButton {
            border: 3px solid transparent;
            border-radius: 0px;
            padding: -2px -4px;
            color: black;
            background-color: transparent;
                min-width:32px;
                min-height:32px;
                max-width:548px;
                max-height:32px;

                font-size: 16px ;
                font-weight: normal ;
                font-family: MiSans;
            }

            QPushButton:hover { background-color: #F0F0F0;}

            QPushButton:pressed { background-color: transparent; }
            QPushButton:checked { background-color: transparent; color: #6329B6; border-bottom: 3px solid #6329B6;}
            QPushButton:disabled { background-color: #EAEAEA; color: #8C8C8C; }
        )");

        QList<QPushButton *>btns = { ui->pushButtonF1, ui->pushButtonF2, ui->pushButtonF3 } ;
        QButtonGroup *pBtnGrp = new QButtonGroup(this) ;
        for(int i=0; i<3; i++)
        {
            QPushButton *btn = btns[i] ;
            btn->setFixedSize(120,24);
            btn->setCheckable(true) ;
            btn->setStyleSheet(strStyle);
            btn->setFocusPolicy(Qt::NoFocus) ;
            btn->setCursor(Qt::PointingHandCursor) ;
            pBtnGrp->addButton(btn,i);
        }

        connect(pBtnGrp,&QButtonGroup::idClicked,this,[=](int id){
            qDebug() << "Function QButtonGroup:" << id ;
        });
        ui->pushButtonF1->click();
    }

}

FrameKeySetting::~FrameKeySetting()
{
    delete ui;
}
