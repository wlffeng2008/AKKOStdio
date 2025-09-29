#include "ModuleLinear.h"
#include "ui_ModuleLinear.h"

ModuleLinear::ModuleLinear(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::ModuleLinear)
{
    ui->setupUi(this);

    ui->verticalSlider2->setStyleSheet(R"(
        QSlider::groove:vertical { width: 24px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #C3FFFD, stop:1 #39E1DC);; border-radius: 12px;}
        QSlider::sub-page:vertical { background: #DCDCDC;  border-radius: 12px; }
        QSlider::handle:vertical {
            width: 32px;
            height: 10px;
            margin: 0 -6px;
            border-radius: 5px;
            background: #7DFFFB ;
            border: 2px solid white;}
        QSlider::handle:hover { background: #F0F0F0;}
        QSlider::handle:pressed { background: #E0E0E0; border-color: #2D7FDD; }
    )");
    connect(ui->verticalSlider1,&QSlider::valueChanged,this,[=](int value){ui->labelValue3->setText(QString::asprintf("%.1fmm",value/10.0));});
    connect(ui->verticalSlider2,&QSlider::valueChanged,this,[=](int value){ui->labelValue4->setText(QString::asprintf("%.1fmm",4.0-value/10.0));});

}

ModuleLinear::~ModuleLinear()
{
    delete ui;
}
