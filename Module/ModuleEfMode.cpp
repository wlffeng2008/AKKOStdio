#include "ModuleEfMode.h"
#include "ui_ModuleEfMode.h"

#include <QButtonGroup>

ModuleEfMode::ModuleEfMode(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::ModuleEfMode)
{
    ui->setupUi(this);

    {
        QString strStyle(R"(

            QPushButton {
                width: 220px;
                height: 32px;
                border-radius: 16px ;
                font-weight:500;

                color: #333;
                border: 1px solid #ECECEC;
                background: #ECECEC; }

            QPushButton:checked {
                color: white;
                border: 1px solid #6329B6;
                background: #6329B6; }
            QPushButton:hover { border: 1px solid #6329B6; }
            )") ;
        QButtonGroup *pBtnGrp = new QButtonGroup(this) ;
        QLayout *pLayout = ui->scrollAreaWidgetContents->layout() ;
        pLayout->setSpacing(8) ;
        pLayout->setContentsMargins(0,0,0,0);

        QStringList strEFList = QString("常亮(默认)、流星、呼吸、涟漪、如影随形、川流不息、繁星点点、霓虹、光波、层出不穷、彩泉涌动、峰回路转、百花争艳、极光、正弦波、雨滴、斜风细雨、踏雪无痕、聚合、一石二鸟、自定义(驱动)、音乐律动电音(驱动)、音乐律动经典(驱动)、光影模式(驱动)").split("、") ;

        for(int i=0; i<strEFList.count(); i++)
        {
            QPushButton *btn = new QPushButton(strEFList[i],this) ;
            btn->setFixedSize(200,44);
            btn->setCheckable(true) ;
            btn->setStyleSheet(strStyle);
            btn->setFocusPolicy(Qt::NoFocus) ;

            pBtnGrp->addButton(btn,i);
            pLayout->addWidget(btn);
            if(i==0)
                btn->click() ;
        }

        connect(pBtnGrp,&QButtonGroup::idClicked,this,[=](int id){
            //qDebug() << "Effect QButtonGroup:" << id ;
           emit onModeChanged(id) ;
        });
    }

}

ModuleEfMode::~ModuleEfMode()
{
    delete ui;
}
