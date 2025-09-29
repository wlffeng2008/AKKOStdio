#include "ModuleEfLumi.h"
#include "ui_ModuleEfLumi.h"

ModuleEfLumi::ModuleEfLumi(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::ModuleEfLumi)
{
    ui->setupUi(this);

    connect(ui->horizontalSlider,&QSlider::valueChanged,this,[=](int value){ui->labelValue->setText(QString::asprintf("%d%%",value*25));});
}

ModuleEfLumi::~ModuleEfLumi()
{
    delete ui;
}
