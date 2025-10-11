#ifndef LINEARFIXING1_H
#define LINEARFIXING1_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class LinearFixing1 : public QDialog
{
    Q_OBJECT

public:
    explicit LinearFixing1(const QString& title,const QString& content, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
};

#endif // LINEARFIXING1_H
