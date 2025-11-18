#include "DialogDeviceConnect.h"
#include "qforeach.h"
#include "ui_DialogDeviceConnect.h"

#include <QTimer>
#include <QDebug>
#include <QMessageBox>
#include <QWindow>


typedef struct{
    QString name ;
    quint8 cmd ;
    quint8 nLen;
    quint8 byte1;

    quint8 byte2;
    quint8 byte3;

    quint8 byte4;
    quint8 byte5;

    quint8 byte6;
    quint8 byte7;

}HidCmd;


static QList<HidCmd> CmdTable =
{
    {"CMD_SET_INFOR",CMD_SET_INFOR,8,0,0,0,0,0,0,0},
    {"CMD_GET_INFOR",CMD_GET_INFOR,8,0,0,0,0,0,0,0},
    {"CMD_SET_RESET",CMD_SET_RESET,8,0,0,0,0,0,0,0},
    {"CMD_GET_RESET",CMD_GET_RESET,8,0,0,0,0,0,0,0},
    {"CMD_SET_BATTERY",CMD_SET_BATTERY,8,0,0,0,0,0,0,0},
    {"CMD_GET_BATTERY",CMD_GET_BATTERY,8,0,0,0,0,0,0,0},
    {"CMD_SET_REPORT",CMD_SET_REPORT,8,0,0,0,0,0,0,0},
    {"CMD_GET_REPORT",CMD_GET_REPORT,8,0,0,0,0,0,0,0},
    {"CMD_SET_PROFILE",CMD_SET_PROFILE,8,0,0,0,0,0,0,0},
    {"CMD_GET_PROFILE",CMD_GET_PROFILE,8,0,0,0,0,0,0,0},
    {"CMD_SET_LEDONOFF",CMD_SET_LEDONOFF,8,1,1,0,0,0,0,0},
    {"CMD_GET_LEDONOFF",CMD_GET_LEDONOFF,8,0,0,0,0,0,0,0},
    {"CMD_SET_DEBOUNCE",CMD_SET_DEBOUNCE,8,0,0,0,0,0,0,0},
    {"CMD_GET_DEBOUNCE",CMD_GET_DEBOUNCE,8,0,0,0,0,0,0,0},
    {"CMD_SET_LEDPARAM",CMD_SET_LEDPARAM,9,1,3,3,7,255,255,255},
    {"CMD_GET_LEDPARAM",CMD_GET_LEDPARAM,9,0,0,0,0,0,0,0},
    {"CMD_SET_SLEDPARAM",CMD_SET_SLEDPARAM,9,1,3,3,7,255,255,255},
    {"CMD_GET_SLEDPARAM",CMD_GET_SLEDPARAM,9,0,0,0,0,0,0,0},
    {"CMD_SET_KBOPTION",CMD_SET_KBOPTION,8,0,0,0,0,0,0,0},
    {"CMD_GET_KBOPTION",CMD_GET_KBOPTION,8,0,0,0,0,0,0,0},
    {"CMD_SET_KEYMATRIX",CMD_SET_KEYMATRIX,8,0,0,0,0,0,0,0},
    {"CMD_GET_KEYMATRIX",CMD_GET_KEYMATRIX,8,0,0,0,0,0,0,0},
    {"CMD_SET_MACRO",CMD_SET_MACRO,8,0,0,0,0,0,0,0},
    {"CMD_GET_MACRO",CMD_GET_MACRO,8,0,0,0,0,0,0,0},
    {"CMD_SET_USERPIC",CMD_SET_USERPIC,8,0,0,0,0,0,0,0},
    {"CMD_GET_USERPIC",CMD_GET_USERPIC,8,0,0,0,0,0,0,0},
    {"CMD_SET_MUSIC",CMD_SET_MUSIC,8,0,0,0,0,0,0,0},
    {"CMD_SET_WINDOWS",CMD_SET_WINDOWS,8,0,0,0,0,0,0,0},
    {"CMD_SET_FN",CMD_SET_FN,8,0,0,0,0,0,0,0},
    {"CMD_GET_FN",CMD_GET_FN,8,0,0,0,0,0,0,0},
    {"CMD_SET_SLEEPTIME",CMD_SET_SLEEPTIME,8,0,0,0,0,0,0,0},
    {"CMD_GET_SLEEPTIME",CMD_GET_SLEEPTIME,8,0,0,0,0,0,0,0},
    {"CMD_SET_USERGIF",CMD_SET_USERGIF,8,0,0,0,0,0,0,0},
    {"",0,8,0,0,0,0,0,0,0}
};

static DialogDeviceConnect *s_connect = nullptr ;
DialogDeviceConnect *DialogDeviceConnect::instance()
{
    return s_connect ;
}

DialogDeviceConnect::DialogDeviceConnect(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogDeviceConnect)
{
    ui->setupUi(this);
    s_connect = this ;
    setWindowFlags(windowFlags()|Qt::MSWindowsFixedSizeDialogHint);
    setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
    connect(ui->checkBoxOntop,&QCheckBox::clicked,this,[=](bool checked){
        QWindow *pWin = windowHandle() ;
        if(checked)
            pWin->setFlags(windowFlags() | Qt::WindowStaysOnTopHint);
        else
            pWin->setFlags(windowFlags() & ~Qt::WindowStaysOnTopHint);
    });

    {
        m_pTable = ui->tableView ;
        m_pModel = new QStandardItemModel() ;
        m_pModel->setHorizontalHeaderLabels(QString("命令,数据长度,Byte0\n命令号,Byte1\nEffect,Byte2\nSpeed,Byte3\nBrightness,Byte4\nOption,Byte5\nR,Byte6\nG,Byte7\nB").split(',')) ;
        m_pTable->setModel(m_pModel) ;

        QHeaderView *pHDV = m_pTable->horizontalHeader() ;
        pHDV->setSectionResizeMode(QHeaderView::Stretch);
        pHDV->setSectionResizeMode(0,QHeaderView::Fixed);
        pHDV->resizeSection(0,150) ;

        foreach(const HidCmd & cmd,CmdTable)
        {
            if(cmd.name.isEmpty())
                continue;
            QStandardItem *item0 = new QStandardItem(cmd.name) ;
            QStandardItem *item1 = new QStandardItem(QString("%1").arg(cmd.nLen)) ;
            QStandardItem *item2 = new QStandardItem(QString("%1").arg(cmd.cmd,2,16,QLatin1Char('0')).toUpper()) ;
            QStandardItem *item3 = new QStandardItem(QString("%1").arg(cmd.byte1)) ;
            QStandardItem *item4 = new QStandardItem(QString("%1").arg(cmd.byte2)) ;
            QStandardItem *item5 = new QStandardItem(QString("%1").arg(cmd.byte3)) ;
            QStandardItem *item6 = new QStandardItem(QString("%1").arg(cmd.byte4)) ;
            QStandardItem *item7 = new QStandardItem(QString("%1").arg(cmd.byte5)) ;
            QStandardItem *item8 = new QStandardItem(QString("%1").arg(cmd.byte6)) ;
            QStandardItem *item9 = new QStandardItem(QString("%1").arg(cmd.byte7)) ;

            QFont font = this->font() ;
            font.setBold(true);

            item0->setEditable(false) ;
            item1->setEditable(false) ;
            item2->setEditable(false) ;

            item0->setForeground(QBrush(Qt::blue)) ;
            if(cmd.nLen == 9)
            {
                item1->setFont(font) ;
                item1->setForeground(QBrush(Qt::red)) ;
                item2->setForeground(QBrush(Qt::green)) ;
                font.setItalic(true);
                item0->setFont(font) ;
                item0->setBackground(QBrush(Qt::white));
            }

            item2->setFont(font) ;
            font.setBold(false);
            font.setItalic(false);

            m_pModel->appendRow({item0,item1,item2,item3,item4,item5,item6,item7,item8,item9});
            m_pTable->setRowHeight(m_pModel->rowCount()-1,20) ;
        }

        connect(m_pModel,&QStandardItemModel::itemChanged,this,[=](QStandardItem *item){
            makeCmd(item->row());
        });
        connect(m_pTable,&QTableView::clicked,this,[=](const QModelIndex &index){
            int row = index.row() ;
            if(m_pModel->item(row,2)->text().toInt(nullptr,16) == CMD_SET_LEDONOFF)
            {
                int col = index.column() ;
                if(col == 3 || col == 4)
                {
                    int val = !m_pModel->item(row,col)->text().toInt();
                    m_pModel->item(row,col)->setText(QString::number(val)) ;
                }
            }
            else
            {
                makeCmd(row);
            }
        });

        connect(m_pTable,&QTableView::doubleClicked,this,[=](const QModelIndex &index){
            int row = index.row() ;
            int col = index.column() ;
            if(col <= 2)
            {
                makeCmd(row,true);
            }
        });

        m_pTable->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(m_pTable,&QTableView::customContextMenuRequested,this,[=](const QPoint &pos){
            const QModelIndex index = m_pTable->indexAt(pos) ;
            int row = index.row() ;
            int col = index.column() ;
            if(col <= 2)
            {
                makeCmd(row,true);
            }
        });
    }

    QTimer *pTMUsb = new QTimer(this) ;
    static USBNotifier *pUsb = new USBNotifier(this);
    QCoreApplication::instance()->installNativeEventFilter(pUsb) ;
    connect(pUsb, &USBNotifier::devicePluggined,this,[=](bool in) {
        qDebug() << "USB device plugged in";
        pTMUsb->stop();
        pTMUsb->start(800) ;
    });

    connect(pTMUsb,&QTimer::timeout,this,[=]{
        pTMUsb->stop();
        ui->pushButtonRefresh->click() ;
    });

    connect(ui->pushButtonRefresh,&QPushButton::clicked,this,[=]{
        disconnect();

        quint32 VID = ui->lineEditVID->text().trimmed().toUInt(nullptr,16) ;
        hid_device_info *pRoot = hid_enumerate(VID,0);
        while(pRoot)
        {
            if(pRoot->usage_page == 0xFFFF)
            {
                if(pRoot->usage == 1)
                {
                    m_pDev0 = hid_open_path(pRoot->path) ;
                    qDebug() << "Open m_pDev0: " << pRoot->path << pRoot->usage << pRoot->usage_page;
                    hid_set_nonblocking(m_pDev0,1) ;
                    ui->labelFlag0->setPixmap(QString(":/images/General_OK4.png"));
                }

                if(pRoot->usage == 2)
                {
                    m_pDev1 = hid_open_path(pRoot->path) ;
                    qDebug() << "Open m_pDev1: " << pRoot->path << pRoot->usage << pRoot->usage_page;
                    ui->labelFlag1->setPixmap(QString(":/images/General_OK4.png"));
                }
            }
            if(m_pDev1 && m_pDev0)
            {
                emit onConnect();
                break;
            }

            pRoot = pRoot->next ;
        }

        if(!m_pDev0 || !m_pDev1)
        {
            emit onDisconnect();
        }
    });

    connect(ui->pushButtonWrite,&QPushButton::clicked,this,[=]{
        if(!m_pDev1) return ;
        QString strCmd = ui->lineEditCmd->text().trimmed(); //"8F 00 00 00 00 00 00 70" ;
        QByteArray data(QByteArray::fromHex(strCmd.toLatin1())) ;
        if(data.size()<8)
        {
            while(data.size()<8) data.append((char)0) ;
            quint8 sum = 0 ;
            for(int i=0; i<7; i++)
                sum += data[i];
            sum = 0xFF - (sum & 0xFF) ;
            data[7] = sum ;
        }
        addReadCmd(data);
        readSetting();
    });

    connect(ui->pushButtonRead,&QPushButton::clicked,this,[=]{

        char buf[1024]={0} ;
        int nlen = hid_get_feature_report(m_pDev1,(quint8 *)buf,65);
        if( nlen>0 )
        {
            QByteArray data(buf+1,nlen-1) ;
            emit onReadBack(data);
            qDebug() << "hid_get_feature_report:" << data.toHex(' ').toUpper();
            quint8 cmd = (quint8)data[0] ;
            switch (cmd)
            {
            case CMD_GET_LEDPARAM:
            case CMD_GET_SLEDPARAM:
            {
                int row = getRow(cmd);
                for(int i=1; i<9; i++)
                {
                    setRowValue(row,2+i,(quint8)data[i]) ;
                }
            }

            break;
            default:
                break;
            }

            addLog(data);
            readSetting();
        }
    });

    m_pRdInput = new QTimer(this) ;
    m_pRdInput->start(20);

    pTMClear = new QTimer(this);
    connect(pTMClear,&QTimer::timeout,this,[=]{
        pTMClear->stop();
        m_bClear=true;
    });

    connect(m_pRdInput,&QTimer::timeout,this,[=]{
        m_pRdInput->stop() ;
        if(m_pDev0)
        {
            char buf[1024] = {0};
            int nlen = hid_read(m_pDev0,(quint8 *)buf,64) ;

            if( nlen>0 )
            {
                QByteArray data(buf,nlen) ;
                qDebug() << "hid_read:" << data.toHex(' ').toUpper();
                addLog(data) ;
            }
        }

        m_pRdInput->start(20) ;
    });

    ui->lineEditCmd->setStyleSheet(" ");
    ui->lineEditPID->setStyleSheet(" ");
    ui->lineEditVID->setStyleSheet(" ");
    ui->lineEditCmd->setStyleSheet("font-family: Fixedsys;");
    ui->lineEditPID->setStyleSheet("font-family: Fixedsys;");
    ui->lineEditVID->setStyleSheet("font-family: Fixedsys;");
    ui->plainTextEdit->setStyleSheet("font-family: Fixedsys;");

    addReadCmd(CMD_GET_REPORT);
    addReadCmd(CMD_GET_PROFILE);
    addReadCmd(CMD_GET_LEDPARAM);
    addReadCmd(CMD_GET_SLEDPARAM);

    for(quint8 i=0; i<4; i++)
    {
        for(quint8 j=0; j<8; j++)
        {
            quint8 tmp[8]={0x8A,0x00,0xFF,j,i,0,0,0} ;
            QByteArray cmd((char *)tmp,8);
            addReadCmd(cmd);
        }
    }
}

DialogDeviceConnect::~DialogDeviceConnect()
{
    delete ui;
}

void DialogDeviceConnect::addLog(const QByteArray&log)
{
    if(m_bClear) ui->plainTextEdit->clear() ;
    QString strLog(log.toHex(' ').toUpper());
    int nLen = strLog.length() ;
    for(int at=nLen-12; at>0; at -= 12)
        strLog.insert(at,' ');
    ui->plainTextEdit->appendPlainText(strLog + "\n") ;
    m_bClear = false ;
    pTMClear->stop();
    pTMClear->start(500);
}

void DialogDeviceConnect::addReadCmd(quint8 cmd, int len)
{
    QByteArray data(len,0);
    data[0]=cmd;
    addReadCmd(data);
}

void DialogDeviceConnect::addReadCmd(QByteArray&cmd)
{
    int len=cmd.size();

    quint8 sum = 0 ;
    for(int i=0; i<len-1; i++)
        sum += cmd[i];
    sum = 0xFF - (sum & 0xFF) ;
    cmd[len-1] = sum ;
    m_readList.push_back(cmd);
}

void DialogDeviceConnect::readSetting()
{
    if(m_readList.count() <= 0)
        return;

    QByteArray cmd = m_readList[0];
    m_readList.pop_front() ;

    qDebug() << "hid_send_feature_report:" << cmd.toHex(' ').toUpper();
    cmd.insert(0,(char)0) ; // report id
    char padding[128]={0} ;
    cmd.append(padding,64);
    hid_send_feature_report(m_pDev1,(quint8 *)cmd.data(),65) ;

    QTimer::singleShot(30,this,[=]{
        ui->pushButtonRead->click() ;
    });
    //makeCmd(getRow(CMD_GET_LEDPARAM),true);
    //QTimer::singleShot(100,this,[=]{ makeCmd(getRow(CMD_GET_SLEDPARAM),true); });
}

void DialogDeviceConnect::startConnect()
{
    ui->pushButtonRefresh->click();
}

void DialogDeviceConnect::makeCmd(int row, bool autoSend)
{
    quint8 buf[32] = {0} ;
    int len = m_pModel->item(row,1)->text().toInt() ;
    buf[0] = m_pModel->item(row,2)->text().toInt(nullptr,16) ;
    if(buf[0]&0x80)
        len = 8 ;
    for(int i=0; i<len-2; i++)
    {
        buf[i+1] = m_pModel->item(row,i + 3)->text().toInt() ;
    }

    quint8 sum = 0 ;
    for(int i=0; i<len-1; i++)
    {
        sum += buf[i] ;
    }
    buf[len-1] = 0xFF - (sum&0xFF) ;

    QByteArray data((char*)buf,len);
    ui->lineEditCmd->setText(data.toHex(' ').toUpper()) ;
    if(autoSend)
        ui->pushButtonWrite->click() ;
}

void DialogDeviceConnect::reset()
{
    makeCmd(getRow(CMD_SET_RESET),true);
}

void DialogDeviceConnect::disconnect()
{
    if(m_pDev0) hid_close(m_pDev0);
    if(m_pDev1) hid_close(m_pDev1);

    m_pDev0 = nullptr ;
    m_pDev1 = nullptr ;

    ui->labelFlag0->setPixmap(QString(":/images/General_NG4.png"));
    ui->labelFlag1->setPixmap(QString(":/images/General_NG4.png"));
}

bool DialogDeviceConnect::nativeEvent(const QByteArray &eventType, void *message, qintptr *result)
{
    MSG* msg = reinterpret_cast<MSG*>(message);
    if (msg->message == WM_DEVICECHANGE)
    {
        switch (msg->wParam)
        {
        case DBT_DEVICEARRIVAL:
        case DBT_DEVICEREMOVECOMPLETE:
            ui->pushButtonRefresh->click() ;
            break;
        }
    }

    return QDialog::nativeEvent(eventType, message, result);
}

int DialogDeviceConnect::getRow(int cmd)
{
    int count = m_pModel->rowCount();
    for(int i=0; i<count; i++)
    {
        int value = m_pModel->item(i,2)->text().toInt(nullptr,16);
        if(value == cmd)
            return i;
    }
    return -1 ;
}

void DialogDeviceConnect::setRowValue(int row, int col, int value)
{
    QStandardItem *item =m_pModel->item(row,col);
    if(item) item->setText(QString::number(value));
}

void DialogDeviceConnect::setLEDOn(bool on)
{
    int row = getRow(CMD_SET_LEDONOFF);
    if(row == -1) return;
    m_bLedOn = on;
    setRowValue(row,3,on?0:1);
    setRowValue(row,4,on?0:1);
    makeCmd(row,true);
}

void DialogDeviceConnect::setLEDPicture(int index)
{
    int row = getRow(CMD_SET_LEDPARAM);
    if(row == -1) return ;

    setRowValue(row,6,0x10 * (index));
    setLEDMode(0x0D);
}

void DialogDeviceConnect::setLEDOption(int option)
{
    int row = getRow(CMD_SET_LEDPARAM);
    if(row == -1) return ;

    setRowValue(row,6,option);
    makeCmd(row,true);
}

void DialogDeviceConnect::setLEDMode(int mode)
{
    // if(!m_bLedOn) setLEDOn(true) ;
    // m_bLedOn = true ;

    int row = getRow(CMD_SET_LEDPARAM);
    if(row == -1) return ;
    setRowValue(row,3,mode);
    if(mode != 0x0D)
    setRowValue(row,6,7);
    makeCmd(row,true);
}

void DialogDeviceConnect::setLEDSpeed(int speed)
{
    int row = getRow(CMD_SET_LEDPARAM);
    if(row == -1) return ;
    setRowValue(row,4,speed);
    makeCmd(row,true);
}

void DialogDeviceConnect::setLEDBright(int bright)
{
    int row = getRow(CMD_SET_LEDPARAM);
    if(row == -1) return ;
    setRowValue(row,5,bright);
    makeCmd(row,true);
}


void DialogDeviceConnect::setLEDColor(const QColor&color,int option)
{
    int row = getRow(CMD_SET_LEDPARAM);
    if(row == -1) return ;
    setRowValue(row,6,option);
    if(option>6)
    {
        setRowValue(row,7,color.red());
        setRowValue(row,8,color.green());
        setRowValue(row,9,color.blue());
    }
    makeCmd(row,true);
}
