#include "FrameMacro.h"
#include "ui_FrameMacro.h"

#include "MacroItem.h"
#include "MacroSquare.h"

#include <QLayout>

static QList<MacroSquare*>s_MSquares;

FrameMacro::FrameMacro(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::FrameMacro)
{
    ui->setupUi(this);

    QString strStyle(R"(

        QPushButton {
            border: 1px solid transparent;
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
        QLayout *pLayout = ui->scrollAreaWidgetContents1->layout() ;
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
        QStringList strEFList = QString("A、B、呼吸、涟漪、如影随形、川流不息、繁星点点、霓虹、光波、层出不穷、彩泉涌动、峰回路转、百花争艳、极光、正弦波、雨滴、斜风细雨、踏雪无痕、聚合、一石二鸟、自定义(驱动)、音乐律动电音(驱动)、音乐律动经典(驱动)、光影模式(驱动)").split("、") ;
        srand(time(nullptr));
        int nCount = strEFList.count() ;
        for(int i=0; i<nCount; i++)
        {
            MacroSquare *btn = new MacroSquare(strEFList[i],rand()%3,this) ;
            btn->setFixedSize(50,50);
            btn->setFocusPolicy(Qt::NoFocus) ;
            s_MSquares.push_back(btn);
        }
        updateView() ;

        connect(ui->pushButtonDelete,&QPushButton::clicked,this,[=]{
            removeView() ;
        });
    }
}

FrameMacro::~FrameMacro()
{
    delete ui;
}

void FrameMacro::updateView()
{
    QGridLayout *pLayout = ui->gridLayout;
    pLayout->setSpacing(8) ;
    pLayout->setContentsMargins(10,10,0,0);
    pLayout->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    while(pLayout->count())
    {
        QWidget *item = pLayout->takeAt(0)->widget();
        if(!item) break ;
        pLayout->removeWidget(item);
    }

    int nCount = s_MSquares.count() ;
    for(int i=0; i<nCount; i++)
    {
        MacroSquare *btn = s_MSquares[i];
        pLayout->addWidget(btn,i/13,i%13);
        btn->setSelected(false) ;
    }
    pLayout->invalidate();
    update() ;
}

void FrameMacro::removeView()
{
    int nCount = s_MSquares.count() ;
    for(int i=nCount-1; i>=0; i--)
    {
        MacroSquare *btn = s_MSquares[i];
        if(btn->isSelected())
        {
            btn->setSelected(false) ;
            btn->hide() ;
            s_MSquares.removeAt(i) ;
        }
    }
    updateView() ;
}
