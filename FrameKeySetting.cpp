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
                height: 40px;
                border-radius: 16px ;
                font-size: 16px ;
                font-weight: bold ;
                font-family: MiSans;

                padding-left: 20px;
                text-align: left ;

                color: #333;
                border: 1px soild #ECECEC;
                background: #ECECEC; }

            QPushButton:checked {
                color: white;
                border: 1px soild #6329B6;
                background: #6329B6; }
            )") ;

        QLayout *pLayout = ui->frameMode->layout() ;
        pLayout->setSpacing(16) ;
        pLayout->setContentsMargins(0,20,0,0);
        pLayout->setAlignment(Qt::AlignTop|Qt::AlignHCenter) ;

        QList<QPushButton *>btns = {ui->pushButtonSet1,ui->pushButtonSet2,ui->pushButtonSet3,ui->pushButtonSet4} ;
        for(int i=0; i<4; i++)
        {
            QPushButton *btn = btns[i] ;
            btn->setFixedSize(120,24);
            btn->setCheckable(true) ;
            btn->setStyleSheet(strStyle);
            btn->setFocusPolicy(Qt::NoFocus) ;
        }

        QButtonGroup *pBtnGrp = new QButtonGroup(this) ;
        pBtnGrp->addButton(ui->pushButtonSet1,0);
        pBtnGrp->addButton(ui->pushButtonSet2,1);
        pBtnGrp->addButton(ui->pushButtonSet3,2);
        pBtnGrp->addButton(ui->pushButtonSet4,4);
        connect(pBtnGrp,&QButtonGroup::idClicked,this,[=](int id){
            qDebug() << "Effect QButtonGroup:" << id ;
        });
    }


    {
        QString strStyleA(R"(
            QPushButton {
                font-size: 16px ;
                font-weight: bold ;
                font-family: MiSans;
                border: none ;

                color: black;
                border-radius: 2px ;
                background: transparent;
                min-width: 60px;
                min-height: 40px;
                max-width:548px;
                max-height:48px;
            }

            QPushButton:checked {
                color: #6329B6;
                border: 2px soild #6329B6;
                background: transparent;
                }
            )") ;

        QString strStyle(R"(

        QPushButton {
            border: 3px solid transparent;
            border-radius: 0px;
            padding: -2px -2px;
            color: black;
            background-color: transparent;
                min-width:40px;
                min-height:32px;
                max-width:548px;
                max-height:32px;

                font-size: 16px ;
                font-weight: bold ;
                font-family: MiSans;
            }

            QPushButton:hover { background-color: #F0F0F0;}

            QPushButton:pressed { background-color: transparent; }
            QPushButton:checked { background-color: transparent; color: #6329B6; border-bottom: 3px solid #6329B6;}
            QPushButton:disabled { background-color: #EAEAEA; color: #8C8C8C; }
        )");

        QList<QPushButton *>btns = { ui->pushButtonF1, ui->pushButtonF2, ui->pushButtonF3 } ;
        for(int i=0; i<3; i++)
        {
            QPushButton *btn = btns[i] ;
            btn->setFixedSize(120,24);
            btn->setCheckable(true) ;
            btn->setStyleSheet(strStyle);
            btn->setFocusPolicy(Qt::NoFocus) ;
        }

        QButtonGroup *pBtnGrp = new QButtonGroup(this) ;
        pBtnGrp->addButton(ui->pushButtonF1,0);
        pBtnGrp->addButton(ui->pushButtonF2,1);
        pBtnGrp->addButton(ui->pushButtonF3,2);
        connect(pBtnGrp,&QButtonGroup::idClicked,this,[=](int id){
            qDebug() << "Function QButtonGroup:" << id ;
        });
    }

}

FrameKeySetting::~FrameKeySetting()
{
    delete ui;
}
