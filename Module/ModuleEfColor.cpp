#include "ModuleEfColor.h"
#include "ui_ModuleEfColor.h"
#include "ColorSlider.h"
#include "ColorSquare.h"
#include <QColorDialog>


static QVector<QColor> col_list;

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
            QTableView{ border: none; background-color: transparent; font: 400 9px "宋体"; }
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
        font.setPointSize(24);
        srand(time(nullptr)) ;

        col_list.push_back(0xE9381D);
        col_list.push_back(0xF4C33C);
        col_list.push_back(0x71FB55);
        col_list.push_back(0x6FEAFC);
        col_list.push_back(0x3000F6);
        col_list.push_back(0xEB35D3);
        col_list.push_back(0xF93030);
        for(int i=0; i<7; i++)
        {
            QStandardItem *item = m_pModel->item(0,i);
            item->setTextAlignment(Qt::AlignBottom|Qt::AlignHCenter) ;
            item->setText("●") ;
            item->setFont(font) ;
            item->setEditable(false) ;
            item->setForeground(QBrush(col_list[i])) ;
        }
        connect(pDele,&ColorDelegate::onClicked,this,[=](int index){
            static quint64 s_pos = 700000000 ;
            s_pos += (index - 3);
            for(int i=0; i<7; i++)
            {
                QStandardItem *item = m_pModel->item(0,i);
                item->setForeground(QBrush(col_list[(i+s_pos)%7])) ;
            }
            ui->tableView->update() ;
        });
    }

    ui->labelAddColor->installEventFilter(this);
    ui->labelAddColor->hide() ;

    ColorSquare *pCSq = new ColorSquare(this);
    ColorSlider *pCSl = new ColorSlider(this);
    pCSl->setRange(0,359) ;

    pCSq->setFixedSize(266,200);
    pCSl->setFixedWidth(266) ;
    ui->verticalLayout->addWidget(pCSq,0,Qt::AlignCenter);
    ui->verticalLayout2->addWidget(pCSl,0,Qt::AlignCenter);

    ui->verticalLayout->setAlignment(Qt::AlignCenter) ;

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
        dialog.setStyleSheet("QPushButton{border:1px solid gray;font: none;background: transparent; color:black; border-radius:0px;}");
        dialog.setWindowTitle("恢复默认样式的颜色对话框");
        dialog.setCurrentColor(Qt::blue);
        if (dialog.exec() == QColorDialog::Accepted) {
            QColor color = dialog.selectedColor();
            qDebug() << color;
        }
    }
    return QFrame::eventFilter(watched,event);
}
