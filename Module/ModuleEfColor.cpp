#include "ModuleEfColor.h"
#include "ui_ModuleEfColor.h"
#include "ColorSlider.h"
#include "ColorSquare.h"
#include <QColorDialog>

ModuleEfColor::ModuleEfColor(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::ModuleEfColor)
{
    ui->setupUi(this);
    ui->tabWidget->setAttribute(Qt::WA_TranslucentBackground);
    ui->tabWidget->setStyleSheet("QWidget{background-color: rgba(0, 0, 0, 0.0);}") ;
    connect(ui->tabWidget,&QTabWidget::currentChanged,this,[=](int index){
        ui->labelBKImage->setHidden(index != 0) ;
    });
    ui->tabWidget->setCurrentIndex(0) ;
    {
        m_pModel = new QStandardItemModel(this) ;
        m_pModel->setHorizontalHeaderLabels(QString("0,0,0,0,0,0,0").split(',')) ;
        ui->tableView->setModel(m_pModel) ;
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch) ;
        ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch) ;
        ui->tableView->setShowGrid(false) ;

        ColorDelegate *pDele = new ColorDelegate(this) ;
        pDele->setTableView(ui->tableView);
        pDele->setImage(":/images/Color-picked.png") ;
        ui->tableView->setItemDelegateForRow(0,pDele);
        ui->tableView->setStyleSheet(R"(
            QTableView{ border: none; background-color: transparent; }
            QTableView::Item::selected{ background-color: transparent; }
        )") ;
        m_pModel->appendRow({
            new QStandardItem("1"),
            new QStandardItem("1"),
            new QStandardItem("1"),
            new QStandardItem("1"),
            new QStandardItem("1"),
            new QStandardItem("1"),
            new QStandardItem("1")
        }) ;
        QFont font = ui->tableView->font() ;
        font.setPointSize(30);
        srand(time(nullptr)) ;
        for(int i=0; i<7; i++)
        {
            QStandardItem *item = m_pModel->item(0,i);
            item->setTextAlignment(Qt::AlignBottom|Qt::AlignHCenter) ;
            item->setText("●") ;
            item->setFont(font) ;
            item->setEditable(false) ;
            item->setForeground(QBrush(QColor(rand()%0x100,rand()%0x100,rand()%0x100))) ;
        }
    }

    ui->labelAddColor->installEventFilter(this);

    ColorSquare *pCSq= new ColorSquare(this);
    ColorSlider *pCSl= new ColorSlider(this);
    pCSl->setRange(0,359) ;

    pCSq->setFixedSize(248,248) ;
    ui->verticalLayout->addWidget(pCSq);
    ui->verticalLayout2->addWidget(pCSl);

    connect(pCSl,&ColorSlider::valueChanged,this,[=](int value){
        pCSq->setHue(value/360.0);
    });
    connect(pCSq,&ColorSquare::colorSelected,this,[=](QColor color){
        ColorLabel::Current(ui->tab2)->setColor(color) ;
    });
}

ModuleEfColor::~ModuleEfColor()
{
    delete ui;
}

bool ModuleEfColor::eventFilter(QObject*watched ,QEvent *event)
{
    if(watched == ui->labelAddColor && event->type() == QEvent::MouseButtonRelease)
    {
        // QColor color = QColorDialog::getColor(Qt::red, nullptr, "选择颜色");
        // if(color.isValid())
        // {
        //     qDebug() << "get Color ......" ;
        // }

        QColorDialog dialog(nullptr);
        dialog.setStyleSheet(nullptr);
        dialog.setWindowTitle("恢复默认样式的颜色对话框");
        dialog.setCurrentColor(Qt::blue);
        if (dialog.exec() == QColorDialog::Accepted) {
            QColor color = dialog.selectedColor();
            qDebug() << color;
            // 使用选中的颜色...
        }
    }
    return QFrame::eventFilter(watched,event);
}
