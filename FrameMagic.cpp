#include "FrameMagic.h"
#include "ui_FrameMagic.h"

#include <QTimer>
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

                padding-left: 25px;
                text-align: left;

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

        QList<QPushButton *>btns = {ui->pushButtonSet1,ui->pushButtonSet2,ui->pushButtonSet3,ui->pushButtonSet4} ;
        QButtonGroup *pBtnGrp = new QButtonGroup(this) ;
        for(int i=0; i<4; i++)
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
            ui->stackedWidget->setCurrentIndex(id) ;
        });
        ui->pushButtonSet1->click() ;
    }

    ui->frameDead->setText("顶部死区","底部死区");

    {
        static QString strStyle1(R"(
        QPushButton {
            border: none;
            border-radius: 0px;
            color: black;
            padding: 0 ;
            background-color: #E4E4E4;
                min-width:20px;
                min-height:20px;
                max-width:20px;
                max-height:20px;

                icon-size: 20px;
            }

            QPushButton:hover { background-color: #E4E4E4;}

            )") ;
        ui->pushButtonM1->setStyleSheet(strStyle1) ;
        ui->pushButtonM2->setStyleSheet(strStyle1) ;
        ui->pushButtonP1->setStyleSheet(strStyle1) ;
        ui->pushButtonP2->setStyleSheet(strStyle1) ;

        static QString strStyle3(R"(

        QLineEdit {
            border: 1px solid #E4E4E4;
            border-radius: 6px;
            min-height: 20px;
            min-width: 60px;
            color: black;
            text-align: center;
            background-color: #E4E4E4;
                font-size: 14px ;
                font-weight: normal ;
                font-family: MiSans;
            }

            QLineEdit:hover { background-color: #F0F0F0;}

            QLineEdit:disabled { background-color: transparent; color: #B7B7B7;border: 1px solid transparent;}
            )") ;

        ui->lineEditValue1->setStyleSheet(strStyle3);
        ui->lineEditValue2->setStyleSheet(strStyle3);
        ui->horizontalSlider2->setStyleSheet(R"(
        QSlider::sub-page:horizontal { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #C3FFFD, stop:1 #39E1DC);  border-radius: 6px;}
        QSlider::handle:horizontal {
            width: 20px;
            height: 16px;
            margin: -6px 0;
            border-radius: 12px;
            background: white;
            border: 2px solid #5CFFFA ; }
        QSlider::handle:hover { background: #F0F0F0;}
        QSlider::handle:pressed { background: #E0E0E0; border-color: #2D7FDD; }
    )");

        ui->horizontalSlider1->setFixedHeight(40) ;
        ui->horizontalSlider2->setFixedHeight(40) ;
        connect(ui->horizontalSlider1,&QSlider::valueChanged,this,[=](int value){ui->lineEditValue1->setText(QString::asprintf("%.03f mm",value/1000.0));});
        connect(ui->horizontalSlider2,&QSlider::valueChanged,this,[=](int value){ui->lineEditValue2->setText(QString::asprintf("%.03f mm",2.7-value/1000.0));});

        ui->horizontalSlider1->setValue(2050) ;
        ui->horizontalSlider2->setValue(1950) ;

        ui->pushButtonM1->setAutoRepeat(true);
        ui->pushButtonM1->setAutoRepeatInterval(100) ;
        connect(ui->pushButtonM1,&QPushButton::pressed,this,[=]{
            int value = ui->horizontalSlider1->value() - 5 ;
            ui->horizontalSlider1->setValue(value);
        }) ;

        ui->pushButtonP1->setAutoRepeat(true);
        ui->pushButtonP1->setAutoRepeatInterval(100) ;
        connect(ui->pushButtonP1,&QPushButton::pressed,this,[=]{
            int value = ui->horizontalSlider1->value() + 5 ;
            ui->horizontalSlider1->setValue(value);
        }) ;

        QTimer *pTMUpdate1 = new QTimer(this) ;
        QTimer *pTMUpdate2 = new QTimer(this) ;

        connect(ui->lineEditValue1,&QLineEdit::textEdited,this,[=](const QString&text){
            pTMUpdate1->stop() ;
            pTMUpdate1->start(300) ;
        });
        connect(pTMUpdate1,&QTimer::timeout,this,[=]{
            pTMUpdate1->stop() ;
            QString strTmp ;
            char szText[100]={0} ;
            strcpy_s(szText,ui->lineEditValue1->text().toStdString().c_str()) ;
            for(int i=0; i<strlen(szText); i++)
            {
                if(szText[i] == '.' || (szText[i] >= '0' && szText[i] <= '9'))
                    continue ;
                szText[i] = 0 ;
                strTmp = szText;
            }
            int value = strTmp.toFloat() * 1000;
            if(value>2500) value = 2500 ;
            if(value<200) value = 200 ;
            ui->horizontalSlider1->setValue(value);
        });

        ui->pushButtonM2->setAutoRepeat(true);
        ui->pushButtonM2->setAutoRepeatInterval(100) ;
        connect(ui->pushButtonM2,&QPushButton::pressed,this,[=]{
            int value = ui->horizontalSlider2->value() - 5 ;
            ui->horizontalSlider2->setValue(value);
        }) ;

        ui->pushButtonP2->setAutoRepeat(true);
        ui->pushButtonP2->setAutoRepeatInterval(100) ;
        connect(ui->pushButtonP2,&QPushButton::pressed,this,[=]{
            int value = ui->horizontalSlider2->value() + 5 ;
            ui->horizontalSlider2->setValue(value);
        }) ;

        connect(ui->lineEditValue2,&QLineEdit::textEdited,this,[=](const QString&text){
            pTMUpdate2->stop();
            pTMUpdate2->start(300);
        });
        connect(pTMUpdate2,&QTimer::timeout,this,[=]{
            pTMUpdate2->stop();
            QString strTmp ;
            char szText[100]={0} ;
            strcpy_s(szText,ui->lineEditValue2->text().toStdString().c_str()) ;
            for(int i=0; i<strlen(szText); i++)
            {
                if(szText[i] == '.' || (szText[i] >= '0' && szText[i] <= '9'))
                    continue ;
                szText[i] = 0 ;
                strTmp = szText;
            }
            int value = strTmp.toFloat() * 1000;
            if(value>2500) value = 2500 ;
            if(value<200) value = 200 ;
            ui->horizontalSlider2->setValue(value);
        });

        connect(ui->checkBox3,&QCheckBox::clicked,this,[=](bool checked){
            ui->labelRelease->setHidden(!checked);
            ui->frameRelease->setHidden(!checked);
        }) ;

        ui->checkBox3->click() ;
    }
}

bool FrameMagic::eventFilter(QObject*watched,QEvent*event)
{
    return QFrame::eventFilter(watched,event);
}

FrameMagic::~FrameMagic()
{
    delete ui;
}
