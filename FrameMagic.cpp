#include "FrameMagic.h"
#include "ui_FrameMagic.h"

#include <QButtonGroup>

FrameMagic::FrameMagic(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::FrameMagic)
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
                background: #ECECEC; }

            QPushButton:checked {
                color: white;
                border: 1px soild #6329B6;
                background: #6329B6; }
            )") ;

        QLayout *pLayout = ui->frameSet->layout() ;
        pLayout->setSpacing(12) ;
        pLayout->setAlignment(Qt::AlignTop|Qt::AlignHCenter) ;

        QList<QPushButton *>btns = {ui->pushButtonSet1,ui->pushButtonSet2,ui->pushButtonSet3,ui->pushButtonSet4,ui->pushButtonSet5} ;
        QButtonGroup *pBtnGrp = new QButtonGroup(this) ;
        for(int i=0; i<5; i++)
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

}

FrameMagic::~FrameMagic()
{
    delete ui;
}
