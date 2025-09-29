#include "ModuleRtSet.h"
#include "ui_ModuleRtSet.h"

#include <QButtonGroup>

ModuleRtSet::ModuleRtSet(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::ModuleRtSet)
{
    ui->setupUi(this);

    {
        static QString strStyle(R"(
            QPushButton {
                min-width: 40px;
                max-width: 40px;
                min-height: 12px;
                max-height: 12px;
                border-radius: 6px ;
                border: 0px soild #B1B1B1;
                background: {{color}}; }
            )") ;

        static QString strDefColor = "#D9D9D9" ;
        static QStringList BKColors = {"#B1B1B1","#A0A0A0","#878787","#6B6B6B","#4E4E4E"};

        static QButtonGroup *pBtnGrp = new QButtonGroup(this) ;

        pBtnGrp->addButton(ui->pushButton_1,0) ;
        pBtnGrp->addButton(ui->pushButton_2,1) ;
        pBtnGrp->addButton(ui->pushButton_3,2) ;
        pBtnGrp->addButton(ui->pushButton_4,3) ;
        pBtnGrp->addButton(ui->pushButton_5,4) ;

        QString strTmp = strStyle ;
        QList<QAbstractButton *>btns = pBtnGrp->buttons() ;
        foreach (QAbstractButton *A, btns) {
            QPushButton *btn = static_cast<QPushButton *>(A) ;
            btn->setText("") ;

            btn->setFocusPolicy(Qt::NoFocus) ;
            btn->setStyleSheet(strTmp.replace("{{color}}",strDefColor));
        }

        connect(pBtnGrp,&QButtonGroup::idClicked,this,[&](int id){
            if(!ui->checkBoxRTMode->getChecked())
                return ;

            for(int i=4; i >= 0; i--)
            {
                QString strColor = BKColors[i] ;
                if(i>id)
                    strColor = strDefColor ;

                QPushButton *btn = static_cast<QPushButton *>(pBtnGrp->button(i)) ;
                QString strTmp = strStyle ;
                btn->setStyleSheet(strTmp.replace("{{color}}",strColor)) ;
            }
        });

        connect(ui->checkBoxRTMode,&QCheckBox::clicked,this,[&](bool checked){
            for(int i=4; i >= 0; i--)
            {
                QString strColor = strDefColor ;
                if(checked && i == 0)
                    strColor = BKColors[0] ;

                QPushButton *btn = static_cast<QPushButton *>(pBtnGrp->button(i)) ;
                QString strTmp = strStyle ;
                btn->setStyleSheet(strTmp.replace("{{color}}",strColor)) ;
            }
        }) ;
    }

}

ModuleRtSet::~ModuleRtSet()
{
    delete ui;
}
