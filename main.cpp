#include "MainWindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "AKKOStudio_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    SetConsoleOutputCP(CP_UTF8);

    QFontDatabase::addApplicationFont(":/font/MiSans-Bold.ttf");
    QFontDatabase::addApplicationFont(":/font/MiSans-Demibold.ttf");
    QFontDatabase::addApplicationFont(":/font/MiSans-ExtraLight.ttf");
    QFontDatabase::addApplicationFont(":/font/MiSans-Heavy.ttf");
    QFontDatabase::addApplicationFont(":/font/MiSans-Light.ttf");
    QFontDatabase::addApplicationFont(":/font/MiSans-Medium.ttf");
    QFontDatabase::addApplicationFont(":/font/MiSans-Normal.ttf");
    QFontDatabase::addApplicationFont(":/font/MiSans-Regular.ttf");
    QFontDatabase::addApplicationFont(":/font/MiSans-Semibold.ttf");
    QFontDatabase::addApplicationFont(":/font/MiSans-Thin.ttf");

    //QApplication::setStyle("Fusion");
    MainWindow w;
    w.show();

    a.setStyleSheet(R"(

        * { font-family: MiSans,MiSans;}
        QLabel { font-size: 14px; font-weight: 500 ;}

        QLabel:disabled { color: #B3B3B3;}
        QLineEdit:disabled { color: #B3B3B3; background-color: #E3E3E3;}

        QLabel#labelTitle1,#labelTitle2,#labelTitle3,#labelTitle4,#labelTitle5,#labelTitle,#labelName { font-size: 18px; font-weight: 600 ;}
        QLabel#labelTitleL1,#labelTitleL2,#labelTitleL3,#labelTitleL4,#labelTitleL5 { font-size: 14px; font-weight: 500 ;}
        QLabel#labelTitleS1,#labelTitleS2,#labelTitleS3,#labelTitleS4,#labelTitleS5 { font-size: 16px; font-weight: 500 ;}
        QLabel#labelValue1,#labelValue5{ font-size: 10px; font-weight: 500 ;}
        QLabel#labelValue2,#labelValue4{ font-size: 14px; font-weight: 500 ;}
        QLabel#labelValue3{ font-size: 18px; font-weight: 600 ;}

        QTableView{ border: 1px solid gray; gridline-color: transparent;  background-color: rgb(226, 249, 255) !important; gridline-color: gray;
                font-size: 10px ;
                font-weight: 500;}
        QTableView::Item{padding-left:2px;  border-top: 0px solid gray; border-bottom: 1px solid transparent;border-right: 0px solid gray;}
        QTableView::Item::selected{ background-color: #a0bb9e !important; color:white; }
        QTableView QTableCornerButton::section { background-color: skyblue ; min-width: 32px; border-top: 0px solid gray; border-bottom: 1px solid gray; border-left: 0px solid gray; border-right: 1px solid gray; }

        QTableView QHeaderView::section{background-color:skyblue;font-size: 10px; font-weight: 400 ;}
        QTableView QHeaderView{background-color:skyblue; font-size: 10px; font-weight: 400 ;}
        QHeaderView::section:horizontal{ font-size: 10px; font-weight: 400 ; padding-left: 2px; border-top: 0px solid gray; border-bottom: 1px solid gray; border-right: 1px solid gray; font-weight: bold;}
        QHeaderView::section:vertical{  padding-left: 2px; min-width: 36px; border-top: 0px solid gray; border-bottom: 1px solid gray; border-left: 0px solid gray; border-right: 1px solid gray;}
        QTableView::indicator { width: 18px; height: 18px; }
        QTableView::indicator:checked { image: url(:/images/BoxChecked.png); }
        QTableView::indicator:unchecked { image: url(:/images/BoxUncheck.png); }
        QHeaderView::section:vertical{ text-align: right;}

        QLineEdit { border: 1px solid gray; border-radius: 4px; }
        QLineEdit:focus{ border: 1px solid #50b7c1; border-radius: 4px;  background-color: rgb(230, 240, 255);}

        QTextEdit {border: 1px solid gray; border-radius: 0px; }
        QTextEdit:focus{ border: 1px solid #50b7c1; border-radius: 4px; background-color: rgb(230, 240, 255);}

        QTableView::indicator:indeterminate { border: 2px solid #888; background-color: #ccc; }

        QLineEdit {border: 1px solid gray; border-radius: 4px; }
        QLineEdit:focus{ border: 1px solid #50b7c1; border-radius: 4px; background-color: rgb(220, 250, 255);}

        QTextEdit {border: 1px solid gray; border-radius: 4px; }
        QTextEdit:focus{ border: 1px solid #50b7c1; border-radius: 4px; background-color: rgb(220, 250, 255);}

        QPushButton {
                background-color: #2D7FDD;
                border-radius: 8px;
                color: white;
                border: 1px solid #6C9F50;
                padding: 1px;
                min-width: 46px;
                min-height: 8px;
                max-width: 800px;
                max-height: 200px;
                font-size: 13px ;
                font-weight: 600;
                }
        QPushButton:hover { background-color: #87ceeb; }
        QPushButton:pressed { background-color: #1e90af; }
        QPushButton:checked { background-color: #1e90ff; }
        QPushButton:disabled { background-color: gray; color: #cccccc;}

        QWidget#pageWakeup QPushButton {
                background-color: red;
                border-radius: 8px;
                color: white;
                border: 1px solid #6C9F50;
                padding: 1px;
                min-width: 46px;
                min-height: 8px;
                max-width: 800px;
                max-height: 200px;
                font-size: 18px ;
                font-weight: 600;
                }
        QWidget#pageWakeup{background-color: #F6F6F6;border-radius:32px;}

        QSlider { border-radius: 12px; }
        QSlider::groove:horizontal { height: 12px; background: #DCDCDC; border-radius: 6px; }
        QSlider::sub-page:horizontal { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #FDDFBA, stop:1 #FFA73C);  border-radius: 6px; }
        QSlider::sub-page:horizontal:disabled { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 white, stop:1 #B3B3B3);  border-radius: 6px; }
        QSlider::handle:horizontal {
            width: 20px;
            height: 16px;
            margin: -6px 0;
            border-radius: 12px;
            background: white;
            border: 2px solid #FFB459; }
        QSlider::handle:horizontal:disabled { border: 2px solid #B3B3B3; }

        QSlider::groove:vertical { width: 24px; background: #DCDCDC; border-radius: 12px; }
        QSlider::sub-page:vertical { background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #FDDFBA, stop:1 #FFA73C);  border-radius: 12px; }
        QSlider::handle:vertical {
            width: 32px;
            height: 10px;
            margin: 0 -6px;
            border-radius: 5px;
            background: #FFAF4E ;
            border: 2px solid white; }

        QSlider::handle:hover { background: #F0F0F0; }
        QSlider::handle:pressed { background: #E0E0E0; border-color: #2D7FDD; }

        QRadioButton { spacing: 5px; color: #333333; font-size: 12px; font-weight: 400 ;}
        QRadioButton::indicator {
            background: transparent;
            border-color: transparent;
            width: 20px;
            height: 20px;
            border: none;
            image: url(:/images/macro/radio-unchecked.png);}

        QRadioButton::indicator:checked { image: url(:/images/macro/radio-checked.png); }

        QRadioButton:disabled { color: #cccccc; }
        QRadioButton:checked {  color: #0085FF; }
        QRadioButton::indicator:disabled { border: 2px solid #dddddd; background: white; }

        QCheckBox { spacing: 5px; color: #333; }
        QCheckBox::indicator { width: 14px; height: 14px; }
        QCheckBox::indicator:unchecked { background: white; border: 2px solid #999; }
        QCheckBox::indicator:checked {
            width: 18px;
            height: 18px;
            background: transparent;
            image: url(:/images/BoxChecked.png);
        }

        QCheckBox::indicator:hover { border-color: #666; }
        QCheckBox:disabled { color: #AAA; }
        QCheckBox::indicator:disabled { background: #EEE; }

        QComboBox {
            border: 1px solid gray;
            border-radius: 4px;
            background: #FFFFFF;
            color: #333333;
            font-weight: normal;
            padding: 2px 2px; }

    QScrollBar:vertical,
    QScrollBar:horizontal {
        background: transparent;
        border: none;
        margin: 0px;
        padding: 0px;
    }

    QScrollBar:vertical {
        width: 4px;
        margin: 0px 0px 0px 0px;
    }

    QScrollBar:horizontal {
        height: 4px;
        margin: 0px 2px 0px 2px;
    }

    QScrollBar::handle:vertical,
    QScrollBar::handle:horizontal {
        background: rgba(160, 160, 160, 0.8);
        border-radius: 2px;
        min-height: 20px;
        min-width: 20px;
    }

    QScrollBar::handle:vertical:hover,
    QScrollBar::handle:horizontal:hover {
        background: rgba(160, 250, 160, 0.7);
    }

    QScrollBar::handle:vertical:pressed,
    QScrollBar::handle:horizontal:pressed {
        background: rgba(160, 250, 160, 0.98);
    }


QScrollBar::add-line:vertical,
QScrollBar::sub-line:vertical,
QScrollBar::add-line:horizontal,
QScrollBar::sub-line:horizontal {
    border: none;
    background: transparent;
    height: 0px;
    width: 0px;
}

QScrollBar::add-page:vertical:hover,
QScrollBar::add-page:horizontal:hover {background: transparent;}
QScrollBar::sub-page:vertical:hover,
QScrollBar::sub-page:horizontal:hover { background: rgba(40, 40, 40, 0.1);}

QScrollBar::add-page:vertical,
QScrollBar::add-page:horizontal {background: transparent;}
QScrollBar::sub-page:vertical,
QScrollBar::sub-page:horizontal { background: transparent;}

QScrollArea { background-color: transparent; }

/*
QScrollArea {
    qproperty-verticalScrollBarPolicy: Qt::ScrollBarAlwaysOff;
    qproperty-horizontalScrollBarPolicy: Qt::ScrollBarAlwaysOff;
}

QScrollArea:hover {
    qproperty-verticalScrollBarPolicy: Qt::ScrollBarAsNeeded;
    qproperty-horizontalScrollBarPolicy: Qt::ScrollBarAsNeeded;
}*/

QTabWidget {
    background-color: transparent;
    border: none;
    border-radius:0;
    padding: 0px;
    margin: 0;
    color: black;
    font-size: 18px;
    font-weight: 400;
}

/* 标签栏的样式 - 水平标签栏 */
QTabBar::tab {
    background-color: transparent;
    border: 3px solid transparent;
    padding: 4px 2px;
    margin-right: 10px;
    min-width: 40px;
    min-height: 40px;
    font-size: 18px;
    font-weight: 400;
}

QTabBar::tab:selected {
    color: #6329B6;
    font-weight: 900;
    border: 3px solid transparent;
    border-bottom: 3px solid #6329B6;
}

QTabBar::tab:hover:!selected {
    background-color: transparent;
    color: #000;
}

QTabBar::tab:vertical {
    min-height: 20px;
    margin-bottom: 10px;
}

QTabWidget::pane {
    background-color: transparent;
    border: none;
    border-radius: 0;
    padding: 0px;
    margin-top: -1px; /* 与标签栏无缝连接 */
}

/* 标签栏下方的分隔线 */
QTabBar::separator {
    width: 1px;
    background-color: #aaa;
}

    )");

    //a.setStyleSheet("");

    return a.exec();
}
