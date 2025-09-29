#ifndef COLORLABEL_H
#define COLORLABEL_H

#include <QLabel>
#include <QObject>
#include <QWidget>

class ColorLabel : public QLabel
{
    Q_OBJECT
public:
    ColorLabel(QWidget *parent=nullptr);
};

#endif // COLORLABEL_H
