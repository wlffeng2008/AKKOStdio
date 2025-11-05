#include "VirtualKeyboard.h"
#include "ui_VirtualKeyboard.h"

VirtualKeyboard::VirtualKeyboard(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::VirtualKeyboard)
{
    ui->setupUi(this);
}

VirtualKeyboard::~VirtualKeyboard()
{
    delete ui;
}
