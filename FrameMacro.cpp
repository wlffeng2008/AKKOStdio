#include "FrameMacro.h"
#include "ui_FrameMacro.h"

FrameMacro::FrameMacro(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::FrameMacro)
{
    ui->setupUi(this);
}

FrameMacro::~FrameMacro()
{
    delete ui;
}
