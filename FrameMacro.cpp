#include "FrameMacro.h"
#include "ui_FrameMacro.h"

#include "MacroItem.h"

#include <QLayout>

FrameMacro::FrameMacro(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::FrameMacro)
{
    ui->setupUi(this);

    QString strStyle(R"(

        QPushButton {
            border: none;
            border-radius: 14px;
            padding: 2px 2px;
            color: black;
            outline: none;
            background-color: transparent;
                min-width:24px;
                min-height:24px;
                max-width:548px;
                max-height:48px; }

            QPushButton:hover { background-color: #FBFBFB; border: 1px solid #FBFBFB;}

            QPushButton:pressed { background-color: #FBFBFB; }
            QPushButton:checked { background-color: #FBFBFB; color:white; }
            QPushButton:disabled { background-color: #EAEAEA; color: #8C8C8C; }
        )");
    setStyleSheet(strStyle);

    {
        QLayout *pLayout = ui->scrollAreaWidgetContents->layout() ;
        pLayout->setSpacing(10) ;
        pLayout->setContentsMargins(5,5,5,5);
        pLayout->setAlignment(Qt::AlignTop|Qt::AlignHCenter);

        for(int i=0; i<5; i++)
        {
            MacroItem *MItem = new MacroItem(this) ;
            MItem->setFixedSize(220,32);
            //MItem->setFocusPolicy(Qt::NoFocus) ;

            pLayout->addWidget(MItem);
        }
    }
    {
        QString strStyle(R"(

        QPushButton {
            border: 1px solid #FBFBFB;
            border-radius: 14px;
            padding: 2px 2px;
            color: black;
            outline: none;
            background-color: #FBFBFB;
                min-width:48px;
                min-height:48px;
                max-width:48px;
                max-height:48px; }

            QPushButton:hover { background-color: #FBFBFB; border: 1px solid #FBFBFB;}

            QPushButton:pressed { background-color: #FBFBFB; }
            QPushButton:checked { background-color: #FBFBFB; color:white; }
            QPushButton:disabled { background-color: #EAEAEA; color: #8C8C8C; }
        )");

        QGridLayout *pLayout = new QGridLayout(this);
        pLayout->setSpacing(8) ;
        pLayout->setContentsMargins(2,2,0,0);
        ui->scrollAreaWidgetContents_2->setLayout(pLayout) ;

        QStringList strEFList = QString("A、B、呼吸、涟漪、如影随形、川流不息、繁星点点、霓虹、光波、层出不穷、彩泉涌动、峰回路转、百花争艳、极光、正弦波、雨滴、斜风细雨、踏雪无痕、聚合、一石二鸟、自定义(驱动)、音乐律动电音(驱动)、音乐律动经典(驱动)、光影模式(驱动)").split("、") ;

        pLayout->setAlignment(Qt::AlignTop|Qt::AlignLeft);
        int nCount = strEFList.count() ;
        for(int i=0; i<nCount; i++)
        {
            QPushButton *btn = new QPushButton(strEFList[i],this) ;
            btn->setFixedSize(48,48);
            btn->setCheckable(true) ;
            btn->setStyleSheet(strStyle);
            btn->setFocusPolicy(Qt::NoFocus) ;

            pLayout->addWidget(btn,i/12,i%12);
        }
    }
}

FrameMacro::~FrameMacro()
{
    delete ui;
}
