#include "FrameMacro.h"
#include "ui_FrameMacro.h"

#include "MacroItem.h"
#include "MacroSquare.h"

#include <QLayout>

static QList<MacroSquare*>s_MSquares;

FrameMacro::FrameMacro(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::FrameMacro)
{
    ui->setupUi(this);

    {
        QLayout *pLayout = ui->scrollAreaWidgetContents1->layout() ;
        pLayout->setSpacing(10) ;
        pLayout->setContentsMargins(5,5,5,5);
        pLayout->setAlignment(Qt::AlignTop|Qt::AlignHCenter);

        for(int i=0; i<5; i++)
        {
            MacroItem *MItem = new MacroItem(this) ;
            MItem->setFixedSize(220,32);
            pLayout->addWidget(MItem);
        }
    }

    {
        srand(time(nullptr));
        for(int i=0; i<26; i++)
        {
            MacroSquare *btn = new MacroSquare(QString((char)('A'+ i)),rand()%3,this) ;
            btn->setFixedSize(50,50);
            btn->setFocusPolicy(Qt::NoFocus) ;
            s_MSquares.push_back(btn);
        }
        updateView() ;

        connect(ui->pushButtonDelete,&QPushButton::clicked,this,[=]{
            removeView() ;
        });

        connect(ui->pushButtonInsert,&QPushButton::clicked,this,[=]{
            for(int i=0; i<10; i++)
            {
                MacroSquare *btn = new MacroSquare(QString((char)('A'+ i)),rand()%3,this) ;
                btn->setFixedSize(50,50);
                btn->setFocusPolicy(Qt::NoFocus) ;
                s_MSquares.insert(rand()%s_MSquares.count(),btn);
            }
            updateView() ;
        });
    }
}

FrameMacro::~FrameMacro()
{
    delete ui;
}

void FrameMacro::updateView()
{
    QGridLayout *pLayout = ui->gridLayout;
    pLayout->setSpacing(8) ;
    pLayout->setContentsMargins(10,10,0,0);
    pLayout->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    while(pLayout->count())
    {
        QWidget *item = pLayout->takeAt(0)->widget();
        if(!item) break ;
        pLayout->removeWidget(item);
    }

    int nCount = s_MSquares.count() ;
    for(int i=0; i<nCount; i++)
    {
        MacroSquare *btn = s_MSquares[i];
        pLayout->addWidget(btn,i/13,i%13);
        btn->setSelected(false) ;
    }
    pLayout->invalidate();
    update() ;
}

void FrameMacro::removeView()
{
    int nCount = s_MSquares.count() ;
    for(int i=nCount-1; i>=0; i--)
    {
        MacroSquare *btn = s_MSquares[i];
        if(btn->isSelected())
        {
            btn->setSelected(false) ;
            btn->hide() ;
            s_MSquares.removeAt(i) ;
        }
    }
    updateView() ;
}
