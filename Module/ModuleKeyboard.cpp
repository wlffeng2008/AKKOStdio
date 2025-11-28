#include "ModuleKeyboard.h"
#include "qdialog.h"
#include "ui_ModuleKeyboard.h"

#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QTimer>

typedef struct __keymap__{
    QString value;
    quint16 hid;
    quint16 code=0;

}keyMapItem;

static QList<keyMapItem> s_keMapTable=
{
    { "`~",  53, 41 },
    { "1!",  30, 2  },
    { "2@",  31, 3  },
    { "3#",  32, 4  },
    { "4$",  33, 5  },
    { "5%",  34, 6  },
    { "6^",  35, 7  },
    { "7&",  36, 8  },
    { "8*",  37, 9  },
    { "9(",  38, 10 },
    { "0)",  39, 11 },
    { "-_",  45, 12 },
    { "=+",  46, 13 },
    { "_¥", 137, 0x0000},
    { "BackSpace", 42,14 },

    { "Tab", 43, 15 },
    { "Q",   20, 16 },
    { "W",   26, 17 },
    { "E",   8 , 18 },
    { "R",   21, 19 },
    { "T",   23, 20 },
    { "Y",   28, 21 },
    { "U",   24, 22 },
    { "I",   12, 23 },
    { "O",   18, 24 },
    { "P",   19, 25 },
    { "[{",  47, 26 },
    { "]}" , 48, 27 },
    { "\\|", 49, 43 },

    { "Caps_Lock", 57,58 },
    { "A",    4, 30 },
    { "S",   22, 31 },
    { "D",    7, 32 },
    { "F",    9, 33 },
    { "G",   10, 34 },
    { "H",   11, 35 },
    { "J",   13, 36 },
    { "K",   14, 37 },
    { "L",   15, 38 },
    { ";:",  51, 39 },
    { "\'\"",  52, 40 },
    { "_]",   50,0x0000 },
    { "Enter", 40,28 },

    { "L_Shift", 0xe1,42 },
    { "L_\\", 100,53 },
    { "Z",  29, 44 },
    { "X",  27, 45 },
    { "C",   6, 46 },
    { "V",  25, 47 },
    { "B",   5, 48 },
    { "N",  17, 49 },
    { "M",  16, 50 },
    { ",<",  54, 51 },
    { ".>",  55, 52 },
    { "/?",  56, 53 },
    { "R_\\"   , 135,43 },
    { "R_Shift", 229,54 },

    { "L_Ctrl", 224,29    },
    { "L_Alt",  226,56    },
    { "Win",    227,57435 },
    { "Menu",   101,57437 },
    { "Space",  44 ,57    },
    { "R_Alt",  230,57400 },
    { "R_Ctrl", 228,57373 },

    { "Insert", 73,57426 },
    { "Delete", 76,57427 },
    { "←"    , 80,75    },
    { "Home",   74,57415 },
    { "End",    77,57423  },
    { "↑",     82,72 },
    { "↓",     81,80 },
    { "Pgup",   75,57417 },
    { "Pgdn",   78,57425 },
    { "→",       79,77 },

    { "Num_Lock", 83,57413 },
    { "Num_7",    95,71 },
    { "Num_Home", 0x4A,71 },
    { "Num_4",    92,75 },
    { "Num_←",   0x50,75 },
    { "Num_1",    89,79 },
    { "Num_End",  0x4D,79 },
    { "Num_/",    84,57397 },
    { "Num_8",    96,72 },
    { "Num_↑",   0x52,72 },
    { "Num_5",    93,76 },
    { "Num_2",    90,80 },
    { "Num_↓",   0x51,80 },
    { "Num_0",    98,82 },
    { "Num_*",    85,55 },
    { "Num_9",    97,73 },
    { "Num_Pgup", 0x4B,73 },
    { "Num_6",    94,77 },
    { "Num_→",   0x4F,77 },
    { "Num_3",    91,81 },
    { "Num_Pgdn", 0x4E,82 },
    { "Num_.",    99,83 },
    { "Num_-",    86,74 },
    { "Num_+",    87,78 },
    { "Num_Enter", 88,57372 },

    { "Esc", 41, 1 },
    { "F1",  58,59 },
    { "F2",  59,60 },
    { "F3",  60,61 },
    { "F4",  61,62 },
    { "F5",  62,63 },
    { "F6",  63,64 },
    { "F7",  64,65 },
    { "F8",  65,66 },
    { "F9",  66,67 },
    { "F10", 67,68 },
    { "F11", 68,87 },
    { "F12", 69,88 },
    { "Print_Screen", 70,57436 },
    { "Scroll_Lock" , 71,   70 },
    { "Pause_Break"       , 72,   69 }
};


static QList<ModuleKeyboard*>s_kbInstance ;


static QString strStyle(R"(
        QPushButton {
                border: 1px solid #EAEAEA;
                color: black;
                background-color: #FBFBFB;
                border-radius: 14px;
                padding: 2px 2px;
                outline: none;
                min-width:42px;
                max-width:542px;
                min-height:42px;
            }

        QPushButton:hover { background-color: #EAEAEA; border: 1px solid #EAEAEA;}
        QPushButton:pressed { background-color: #3F3F3F; }
        QPushButton:checked { background-color: #3F3F3F; color: white; }
        QPushButton:disabled { background-color: #EAEAEA; color: #8C8C8C; }
        )");

ModuleKeyboard::ModuleKeyboard(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::ModuleKeyboard)
{
    ui->setupUi(this);

    setMinimumHeight(400) ;
    setMinimumWidth(960) ;

    QTimer::singleShot(100,this,[=]{
        if(parent)
        {
            //parent->setMinimumSize(960,400) ;
            //parent->layout()->setAlignment(Qt::AlignCenter);
            //qDebug() << "parent->parentWidget()->layout()->setAlignment(Qt::AlignCenter)";
        }
    });
    int nIndex = 0 ;
    for(int i=0; i<0xFFFF; i++)
    {
        QString strName = QString::asprintf("pushButton_%04X",i) ;
        QPushButton *btn = findChild<QPushButton*>(strName) ;
        if(!btn) continue;
        btn->setStyleSheet(strStyle);
        btn->setCheckable(true) ;
        btn->setFocusPolicy(Qt::NoFocus);
        btn->setCursor(Qt::PointingHandCursor) ;
        ui->buttonGroup->removeButton(btn);
        ui->buttonGroup->addButton(btn,nIndex++) ;
        if(i== 0xE000) m_spcBtn = btn ;
    }

    QTimer::singleShot(100,this,[=]{m_spcBtn->setStyleSheet(strStyle + "QPushButton{ border-radius:24px;}");}) ;

    ui->buttonGroup->setExclusive(false) ;

    connect(ui->buttonGroup,&QButtonGroup::idClicked,this,[=](int id){

        const QList<QAbstractButton*>btns = ui->buttonGroup->buttons();
        int nChecked = 0;
        for(QAbstractButton*btn:btns)
        {
            if(nChecked >= m_nSelectCount)
            {
                btn->setChecked(false);
                continue ;
            }

            if(btn->isChecked())
                nChecked++ ;
        }

        QPushButton *btn = static_cast<QPushButton *>(ui->buttonGroup->button(id)) ;
        emit onKeyClicked(btn->text()) ;
        // qDebug() << "Clicked:" << id << btn->objectName() ;
    });

    m_Menu = new CustomTooltip() ;
    m_Menu->setTextStyle("QLabel { color: red; }") ;

    connect(m_Menu,&CustomTooltip::onClicked,this,[=]{
        if(m_curBtn->isEnabled())
        {
            m_curBtn->setEnabled(false);
            m_curBtn->installEventFilter(this);
            m_disables.push_back(m_curBtn);
        }
        else
        {
            m_curBtn->removeEventFilter(this);
            m_disables.removeAll(m_curBtn);
            m_curBtn->setEnabled(true);
        }
        setKeyEnable(m_curBtn->objectName(),m_curBtn->isEnabled(),true);
    }) ;

    s_kbInstance.push_back(this);
}

ModuleKeyboard::~ModuleKeyboard()
{
    s_kbInstance.removeAll(this);
    delete ui;
}

void ModuleKeyboard::setSelectCount(int count)
{
    m_nSelectCount = count;
    ui->buttonGroup->setExclusive(false);
}

void ModuleKeyboard::setSingleMode(bool set)
{
    ui->buttonGroup->setExclusive(set);
}

void ModuleKeyboard::keyPressEvent(QKeyEvent *event)
{
    //qDebug() << "ModuleKeyboard::keyPressEvent" << event->nativeVirtualKey();
    QFrame::keyPressEvent(event);
}

void ModuleKeyboard::showFlag(bool show)
{
    ui->frameFlag->setVisible(show);
}

void ModuleKeyboard::setKeyEnable(const QString&objname,bool bEnable,bool bSetToAll)
{
    if(m_bFixMode) return;

    QPushButton *btn = findChild<QPushButton*>(objname);
    if(btn) btn->setEnabled(bEnable);

    if(!bSetToAll) return;

    for(ModuleKeyboard*pkb:s_kbInstance)
        pkb->setKeyEnable(objname,bEnable,false);
}

void ModuleKeyboard::setkeyHited(int id)
{
    int nCode = id ;
    if(nCode == 0) nCode = 0x81;

    QString strName = QString::asprintf("pushButton_%04X",nCode);
    QPushButton *btn = findChild<QPushButton*>(strName);
    if(btn)
    {
        btn->setStyleSheet(strStyle + R"(
            QPushButton:disabled { background-color: #FF9052; color: white; }
        )") ;
    }
}

void ModuleKeyboard::setKeyFixMode()
{
    ui->frameFlag->hide();

    QTimer::singleShot(10,this,[=]{
        m_bFixMode = true;
        const QList<QAbstractButton*>btns = ui->buttonGroup->buttons();
        for(QAbstractButton*btn:btns)
        {
            btn->setEnabled(false);
            btn->setStyleSheet(strStyle + "QPushButton:disabled { background-color: white; color: black; }" +
                               (m_spcBtn == btn ? "QPushButton{ border-radius:24px;}":""));
        }
        update();
    });
}

void ModuleKeyboard::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);

    if(m_draging && !m_bFixMode)
    {
        QPainter painter(this);
        QRect rect(m_clkPt,m_nowPt);

        painter.setBrush(Qt::NoBrush);
        painter.setPen(QPen(QBrush(Qt::blue),2,Qt::DashLine));
        painter.drawRect(rect);
    }
}

bool ModuleKeyboard::event(QEvent *event)
{
    if(event->type() == QEvent::MouseButtonRelease)
    {
        m_draging=false;
        QMouseEvent *pME = static_cast<QMouseEvent *>(event);
        if(pME->button() == Qt::RightButton && m_Menu)
        {
            QPoint clkPt = mapFromGlobal(cursor().pos());
            const QList<QAbstractButton*>btns = ui->buttonGroup->buttons();
            for(QAbstractButton*btn:btns)
            {
                if(btn->geometry().contains(clkPt))
                {
                    m_curBtn = btn;
                    m_Menu->setText(tr("禁用该按键")) ;
                    QPoint pos = btn->mapToGlobal(QPoint(btn->width()+5,(btn->height() - m_Menu->height())/2));
                    m_Menu->move(pos);
                    m_Menu->show();
                    break;
                }
            }
        }
        update();
    }
    return QFrame::event(event) ;
}

bool ModuleKeyboard::eventFilter(QObject *watched,QEvent *event)
{
    if(event->type() == QEvent::MouseButtonRelease)
    {
        QMouseEvent *pME = static_cast<QMouseEvent *>(event) ;
        if(pME->button() == Qt::RightButton && m_Menu)
        {
            for(QAbstractButton*btn:m_disables)
            {
                if(btn == watched)
                {
                    m_curBtn = btn;
                    m_Menu->setText(tr("取消禁用")) ;
                    QPoint pos = btn->mapToGlobal(QPoint(btn->width()+5,(btn->height() - m_Menu->height())/2));
                    m_Menu->move(pos);
                    m_Menu->show();
                    break;
                }
            }
            update();
        }
    }
    return QFrame::eventFilter(watched,event);
}

void ModuleKeyboard::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && !m_bFixMode)
    {
        m_clkPt = event->pos();
        m_nowPt = event->pos();
        m_draging=true;
        update();
    }
    QFrame::mousePressEvent(event);
}

void ModuleKeyboard::mouseMoveEvent(QMouseEvent *event)
{
    if(m_draging && m_clkPt.x()>0)
    {
        m_nowPt = event->pos() ;
        QRect rect(m_clkPt,m_nowPt);

        const QList<QAbstractButton*>btns = ui->buttonGroup->buttons() ;
        for(QAbstractButton*btn:btns)
        {
            QRect btnRc = btn->rect();
            btn->setChecked(
                rect.contains( btn->mapToParent(btnRc.topLeft()))    ||
                rect.contains( btn->mapToParent(btnRc.topRight()))   ||
                rect.contains( btn->mapToParent(btnRc.bottomLeft())) ||
                rect.contains( btn->mapToParent(btnRc.bottomRight()))
                );
        }

        update();
    }

    QFrame::mouseMoveEvent(event);
}

void ModuleKeyboard::mouseReleaseEvent(QMouseEvent *event)
{
    m_draging=false;
    m_clkPt = event->pos();
    update();

    QFrame::mouseReleaseEvent(event);
}
