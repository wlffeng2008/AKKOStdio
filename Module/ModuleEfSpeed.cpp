#include "ModuleEfSpeed.h"
#include "ui_ModuleEfSpeed.h"

ModuleEfSpeed::ModuleEfSpeed(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::ModuleEfSpeed)
{
    ui->setupUi(this);

    ui->horizontalSlider->setStyleSheet(R"(
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
    connect(ui->horizontalSlider,&QSlider::valueChanged,this,[=](int value){ui->labelValue->setText(QString::asprintf("%d%%",value*25));});
}

ModuleEfSpeed::~ModuleEfSpeed()
{
    delete ui;
}
