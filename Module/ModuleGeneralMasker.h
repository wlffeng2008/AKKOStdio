#ifndef MODULEGENERALMASKER_H
#define MODULEGENERALMASKER_H

#include <QDialog>
#include <QVBoxLayout>

class ModuleGeneralMasker : public QDialog
{
    Q_OBJECT
public:
    ModuleGeneralMasker(QWidget *cotnent, QWidget *parent=nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    bool eventFilter(QObject*watched, QEvent*event) override;

private:
    QWidget *m_watch = nullptr;
    QVBoxLayout*m_layout = nullptr;
};

#endif // MODULEGENERALMASKER_H
