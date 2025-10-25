#include "ModuleRtSet.h"
#include "ui_ModuleRtSet.h"

#include <QButtonGroup>
#include <QPainter>
#include <QEvent>
#include <QMouseEvent>
#include <QTimer>


static QRect s_Rect ;
static float value = 0.5 ;
static float valueMin = 0.2 ;
static float valueMax = 2.5 ;

ModuleRtSet::ModuleRtSet(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::ModuleRtSet)
{
    ui->setupUi(this);

    // {
        static QString strStyle1(R"(
        QPushButton {
            border: 3px solid transparent;
            border-radius: 0px;
            color: black;
            background-color: transparent;
                min-width:20px;
                min-height:20px;
                max-width:20px;
                max-height:20px;

                font-size: 16px ;
                font-weight: bold ;
                font-family: MiSans;
                icon: url(:/images//rt/plug-normal.png);
                icon-size: 20px;
            }

            QPushButton:hover { background-color: #F0F0F0;}

            QPushButton:pressed { background-color: transparent; }
            QPushButton:checked { background-color: transparent; color: #6329B6; border-bottom: 3px solid #6329B6;}
            QPushButton:disabled { background-color: transparent; color: transparent; icon: url(:/images/rt/plug-disabled.png);}
            )") ;
    ui->pushButtonPlug->setStyleSheet(strStyle1) ;

        static QString strStyle2(R"(
        QPushButton {
            border: 3px solid transparent;
            border-radius: 0px;
            color: black;
            background-color: transparent;
                min-width:20px;
                min-height:20px;
                max-width:20px;
                max-height:20px;
                icon: url(:/images/rt/minus-normal.png);
                icon-size: 20px;
            }

            QPushButton:hover { background-color: #F0F0F0;}

            QPushButton:pressed { background-color: transparent; }
            QPushButton:checked { background-color: transparent; color: #6329B6; border-bottom: 3px solid #6329B6;}
            QPushButton:disabled { background-color: transparent; color: transparent; icon: url(:/images/rt/minus-disabled.png);}
            )") ;
    ui->pushButtonMinus->setStyleSheet(strStyle2) ;

        static QString strStyle3(R"(

        QLineEdit {
            border: 1px solid #EDEDED;
            background-color: #EDEDED;
            border-radius: 6px;
            min-height: 20px;
            color: black;
            text-align: center;
            }

            QLineEdit:hover { background-color: #F0F0F0;}

            QLineEdit:disabled { background-color: transparent; color: #B7B7B7;border: 1px solid transparent;}
            )") ;

        ui->lineEdit->setStyleSheet(strStyle3);

        connect(ui->checkBoxRTMode,&QCheckBox::clicked,this,[&](bool checked){
            ui->pushButtonMinus->setEnabled(checked);
            ui->pushButtonPlug->setEnabled(checked);
            ui->lineEdit->setEnabled(checked);
            update() ;
        }) ;
    // }

        ui->checkBoxRTMode->setChecked(true);

        connect(ui->lineEdit,&QLineEdit::textEdited,this,[=](const QString &text){
            value = getValue() ;
            update() ;
        });

        ui->pushButtonMinus->setAutoRepeat(true);
        ui->pushButtonMinus->setAutoRepeatInterval(100) ;
        connect(ui->pushButtonMinus,&QPushButton::pressed,this,[=]{
            value = getValue() - 0.005 ;
            setValue(value) ;
        }) ;

        ui->pushButtonPlug->setAutoRepeat(true);
        ui->pushButtonPlug->setAutoRepeatInterval(100) ;
        connect(ui->pushButtonPlug,&QPushButton::pressed,this,[=]{
            value = getValue() + 0.005 ;
            setValue(value) ;
            update() ;
        }) ;

    installEventFilter(this) ;
    setMouseTracking(true) ;
}

ModuleRtSet::~ModuleRtSet()
{
    delete ui;
}

void ModuleRtSet::setValue(float value)
{
    float tmp = value ;

    if(tmp<valueMin) tmp=valueMin ;
    if(tmp>valueMax) tmp=valueMax ;

    ui->lineEdit->setText(QString::asprintf("%.3f mm",tmp)) ;

    update() ;
}

float ModuleRtSet::getValue()
{
    QString text = ui->lineEdit->text() ;
    char szText[100]={0} ;
    strcpy_s(szText,text.toStdString().c_str()) ;
    for(int i=0; i<strlen(szText); i++)
    {
        if(szText[i] == '.' || (szText[i] >= '0' && szText[i] <= '9'))
            continue ;
        szText[i] = 0 ;
        break;
    }
    text = szText;

    float tmp = text.toFloat() ;

    if(tmp<valueMin)
    {
        tmp = valueMin ;
        setValue(tmp) ;
    }
    if(tmp>valueMax)
    {
        tmp=valueMax ;
        setValue(tmp) ;
    }
    return tmp ;
}

bool ModuleRtSet::eventFilter(QObject*watched,QEvent*event)
{
    if(event->type() == QEvent::MouseButtonPress && ui->checkBoxRTMode->getChecked())
    {
        QMouseEvent *pEV = static_cast<QMouseEvent *>(event);
        QRect tmp = s_Rect.adjusted(-2,0,2,0) ;
        if(tmp.contains(pEV->pos()))
        {
            m_dragging = true ;
            value = (pEV->pos().x() - s_Rect.left()) * (valueMax-valueMin) / s_Rect.width() + valueMin ;
            setValue(value) ;
        }
    }

    if(event->type() == QEvent::MouseButtonRelease)
    {
        m_dragging = false ;
    }

    if(event->type() == QEvent::MouseMove)
    {
        if(m_dragging)
        {
            QMouseEvent *pEV = static_cast<QMouseEvent *>(event);
            QRect tmp = s_Rect.adjusted(-2,0,2,0) ;
            if(tmp.contains(pEV->pos()))
            {
                m_dragging = true ;
                value = (pEV->pos().x() - s_Rect.left()) * (valueMax-valueMin) / s_Rect.width() + valueMin ;
                setValue(value) ;
            }
        }
    }

    return QFrame::eventFilter(watched,event);
}

void ModuleRtSet::paintEvent(QPaintEvent *event)
{
    QPainter painter(this) ;
    QPen Black(Qt::black,1) ;
    painter.setBrush(Qt::black) ;
    if(!ui->checkBoxRTMode->getChecked())
    {
        painter.setBrush(0xB7B7B7) ;
        Black.setColor(0xB7B7B7);
    }
    painter.setPen(Black) ;
    s_Rect = QRect(20,50,260,50);
    int nCount = 20 ;
    qreal xStep = s_Rect.width()*1.0/(nCount-1) ;
    for(int i=0; i<nCount; i++)
    {
        painter.drawLine(QPoint(s_Rect.left()+i*xStep,85),QPoint(s_Rect.left()+i*xStep,100)) ;
    }

    int nTriLen = 10;
    float value = getValue();
    int nImgX = s_Rect.left() + s_Rect.width() * (value - valueMin) / (valueMax - valueMin) - nTriLen/2 ;


    painter.drawLine(QPoint(nImgX+nTriLen/2,72),QPoint(nImgX+nTriLen/2,100)) ;
    painter.setRenderHint(QPainter::Antialiasing,true) ;

    QPolygonF triangle;
    triangle<<QPoint(nImgX,s_Rect.top()) ;
    triangle<<QPoint(nImgX+nTriLen,s_Rect.top()) ;
    triangle<<QPoint(nImgX+nTriLen/2,s_Rect.top() + nTriLen/2 * sqrt(3)) ;
    painter.drawPolygon(triangle);

}
