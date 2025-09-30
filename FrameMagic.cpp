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
                height: 40px;
                border-radius: 16px ;
                font-size: 16px ;
                font-weight: bold ;
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
        pLayout->setContentsMargins(0,10,0,0);
        pLayout->setAlignment(Qt::AlignTop|Qt::AlignHCenter) ;

        QList<QPushButton *>btns = {ui->pushButtonSet1,ui->pushButtonSet2,ui->pushButtonSet3,ui->pushButtonSet4,ui->pushButtonSet5} ;
        for(int i=0; i<5; i++)
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
        pBtnGrp->addButton(ui->pushButtonSet4,3);
        pBtnGrp->addButton(ui->pushButtonSet5,4);
        connect(pBtnGrp,&QButtonGroup::idClicked,this,[=](int id){
            qDebug() << "Effect QButtonGroup:" << id ;
        });
    }

}

FrameMagic::~FrameMagic()
{
    delete ui;
}
