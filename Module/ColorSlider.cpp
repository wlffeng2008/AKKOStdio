#include "ColorSlider.h"

#include <QPainter>
#include <QMouseEvent>
#include <QStyleOptionSlider>

ColorSlider::ColorSlider(QWidget *parent) : QSlider(parent)
{
    //col_list.push_back(Qt::black);
    col_list.push_back(0xE9381D);
    col_list.push_back(0xF4C33C);
    col_list.push_back(0x71FB55);
    col_list.push_back(0x6FEAFC);
    col_list.push_back(0x3000F6);
    col_list.push_back(0xEB35D3);
    col_list.push_back(0xE93738);
    //col_list.push_back(Qt::white);

    setOrientation(Qt::Horizontal);
}

void ColorSlider::mousePressEvent(QMouseEvent *event)
{
    QSlider::mousePressEvent(event);
    if(event->button() == Qt::LeftButton)
    {
        int w = width() ;
        setValue(mapFromGlobal(cursor().pos()).x()*(maximum()) / w) ;
    }
}


void ColorSlider::setColors(const QVector<QColor> &bg)
{
    col_list = bg;
    update();
}

void ColorSlider::setGradient(const QLinearGradient &bg)
{
    col_list.clear();
    foreach(const QGradientStop& gs, bg.stops() )
    {
        col_list.push_back(gs.second);
    }
    update();
}

QLinearGradient ColorSlider::gradient() const
{
    int ior = orientation() == Qt::Horizontal ? 1 : 0;
    QLinearGradient lg(0, 0, ior, 1-ior);
    lg.setCoordinateMode(QGradient::StretchToDeviceMode);
    for(int i = 0; i < col_list.size(); i++)
        lg.setColorAt(double(i) / (col_list.size() - 1), col_list[i]);
    return lg;
}

void ColorSlider::paintEvent(QPaintEvent *ev)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    const int offset = 8;
    QRect rect = this->rect();
    rect.setHeight(16);
    QRect sliderRect = rect;

    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::NoPen);
    painter.setBrush(gradient());
    painter.drawRoundedRect(sliderRect,8,8);

    const double k = (double)(value() - minimum()) / (maximum()-minimum());
    int x = (int)((rect.width()-2*offset) * k) + offset;

    painter.save();
    QPen pen1(Qt::white, 3);
    painter.setPen(pen1);
    painter.drawEllipse(QPointF(x, 8), 8, 8);
    painter.restore();
}
