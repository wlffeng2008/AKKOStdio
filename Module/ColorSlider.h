#ifndef COLORSLIDER_H
#define COLORSLIDER_H

#include <QObject>
#include <QSlider>

class ColorSlider : public QSlider
{
    Q_OBJECT

public:
    explicit ColorSlider(QWidget *parent = 0);

    QVector<QColor> colors() const { return col_list; }
    void setColors(const QVector<QColor> &bg);

    void setGradient(const QLinearGradient &bg);
    QLinearGradient gradient() const ;

protected:
    void paintEvent(QPaintEvent *ev) override;
    void mousePressEvent(QMouseEvent *event) override ;

private:
    QVector<QColor> col_list;
};

#endif // COLORSLIDER_H
