#include "ModuleVideoItem.h"
#include "ui_ModuleVideoItem.h"

ModuleVideoItem::ModuleVideoItem(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::ModuleVideoItem)
{
    ui->setupUi(this);
}

ModuleVideoItem::~ModuleVideoItem()
{
    delete ui;
}
