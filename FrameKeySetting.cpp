#include "FrameKeySetting.h"
#include "ui_FrameKeySetting.h"

#include <QTimer>
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
                max-height: 32px;
                min-height: 32px;
                border-radius: 16px ;

                padding-left: 25px;
                text-align: left;

                color: #333;
                border: 1px solid transparent;
                background: transparent; }

            QPushButton:checked {
                color: white;
                border: 1px solid #6329B6;
                background: #6329B6; }
            QPushButton:hover {border: 1px solid #6329B6; }
            )") ;

        QLayout *pLayout = ui->frameMode->layout() ;
        pLayout->setSpacing(12) ;
        pLayout->setAlignment(Qt::AlignTop|Qt::AlignHCenter) ;

        QList<QPushButton *>btns = {ui->pushButtonSet1,ui->pushButtonSet2,ui->pushButtonSet3} ;
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
            ui->stackedWidget->setCurrentIndex(id) ;
        });
        ui->pushButtonSet1->click() ;
    }
    {
        QStringList Files={
            "fn.png",
            "kuaijin.png",
            "houtui.png",
            "zanting.png",
            "guanbiyinliang.png",
            "yinliangjia.png",
            "yinliangjian.png",
            "yinyue.png",
            "jisuanqi.png",
            "youjian.png",
            "frame.png",
            "sousuo.png",
            "shouye.png",
            "shuaxin.png",
            "jianpanliangdujia.png",
            "jianpanliangdu.png",
            "fangda.png",
            "suoxiao.png",
            "yuyin.png" };
        QButtonGroup *pBtnGrp = new QButtonGroup(this) ;
        for(int i=0; i<19; i++)
        {
            QString strName = QString::asprintf("pushButton_F%02d",i+1) ;
            QPushButton *btn = findChild<QPushButton*>(strName) ;
            if(!btn) continue;

            btn->setCheckable(true) ;
            btn->setText("") ;

            QString strStyle=QString(R"(
                QPushButton {
                    icon: url(:/images/macro/fn0/%1);
                    icon-size: 24px 24px;
                    border-radius: 16px ;
                    border: 1px soild #ECECEC;
                    background: #FFFFFF;
                    padding: 2px; }

                QPushButton:checked,pressed {
                    icon: url(:/images/macro/fn1/%2);
                    background-color: #3F3F3F; }

                QPushButton:hover {
                    icon: url(:/images/macro/fn1/%3);
                    background-color: #8F8F8F; }
            )").arg(Files[i],Files[i],Files[i]);

            btn->setStyleSheet(strStyle);
            btn->setFocusPolicy(Qt::NoFocus) ;
            btn->setCursor(Qt::PointingHandCursor) ;
            pBtnGrp->addButton(btn,i);
        }
    }
    {
        QStringList Values1 ={"1000 hz","2000 hz","3000 hz","4000 hz","5000 hz","6000 hz","7000 hz","8000 hz"} ;
        ui->frameSV1->setValueList(Values1) ;

        QStringList Values2 ={"5 min","15 min","30 min","45 min","60 min"} ;
        ui->frameSV2->setValueList(Values2) ;
        ui->frameSV3->setValueList(Values2) ;

        ui->horizontalSlider->setFixedHeight(40) ;
        connect(ui->horizontalSlider,&QSlider::valueChanged,this,[=](int value){ui->lineEditValue->setText(QString::asprintf("%d ms",value));});

        ui->horizontalSlider->setValue(25) ;

        QTimer *pTMUpdate = new QTimer(this) ;
        connect(pTMUpdate,&QTimer::timeout,this,[=]{
            pTMUpdate->stop();
            QString strTmp = ui->lineEditValue->text().trimmed();
            char szText[100]={0} ;
            strcpy_s(szText,strTmp.toStdString().c_str()) ;
            for(int i=0; i<strlen(szText); i++)
            {
                if(szText[i] == '.' || (szText[i] >= '0' && szText[i] <= '9'))
                    continue ;
                szText[i] = 0 ;
                break;
            }
            strTmp = szText;
            int value = strTmp.toFloat() ;
            if(value>200) value = 200 ;
            if(value<0) value = 0 ;
            ui->horizontalSlider->setValue(value);
        });

        connect(ui->lineEditValue,&QLineEdit::textEdited,this,[=](const QString&text){
            pTMUpdate->stop() ;
            pTMUpdate->start(300) ;
        });
    }
}

FrameKeySetting::~FrameKeySetting()
{
    delete ui;
}
