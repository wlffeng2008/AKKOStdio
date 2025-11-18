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
        pBtnGrp = new QButtonGroup(this) ;
        QLayout *pLayout = ui->scrollAreaWidgetContents->layout() ;
        pLayout->setSpacing(8) ;
        pLayout->setContentsMargins(0,0,0,0);

        QStringList strEFList = QString("关闭,常亮,呼吸,光谱循环,光波,涟漪,繁星点点,川流不息,如影随形,聚合,彩泉涌动,百花争艳,自定义,一石二鸟,峰回路转,斜风细雨,雨滴,流星,踏雪无痕,正弦波,音乐律动3,光影,音乐律动2,极光,层出不穷,灯效编辑").split(",") ;

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
            if(!m_bOutSet)
                emit onModeChanged(id) ;
            m_bOutSet=false;
        });
        ui->checkBoxEFMode->hide() ;
    }
}

ModuleEfMode::~ModuleEfMode()
{
    delete ui;
}

void ModuleEfMode::setEfMode(int mode)
{
    m_bOutSet =true;
    pBtnGrp->button(mode)->click();
}
