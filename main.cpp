#include "MainWindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

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

    //QApplication::setStyle("Fusion");
    MainWindow w;
    w.show();

    a.setStyleSheet(R"(

        QTableView{ border: 1px solid gray; gridline-color: transparent;  background-color: rgb(226, 249, 255) !important; gridline-color: gray;}
        QTableView::Item{padding-left:2px;  border-top: 0px solid gray; border-bottom: 1px solid transparent;border-right: 0px solid gray;}
        QTableView::Item::selected{ background-color: #a0bb9e !important; color:white; }
        QTableView QTableCornerButton::section { background-color: skyblue ; min-width: 32px; border-top: 0px solid gray; border-bottom: 1px solid gray; border-left: 0px solid gray; border-right: 1px solid gray; }

        QTableView QHeaderView::section{background-color:skyblue;}
        QTableView QHeaderView{background-color:skyblue;}
        QHeaderView::section:horizontal{  padding-left: 2px; border-top: 0px solid gray; border-bottom: 1px solid gray; border-right: 1px solid gray; font-weight: bold;}
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
                background-color: #6C9F50;
                border-radius: 8px;
                color: white;
                border: 2px solid gray;
                padding: 2px 2px;
                min-width: 60px;
                min-height: 12px; }

        QPushButton:hover { background-color: #87ceeb; }
        QPushButton:pressed { background-color: #1e90af; }
        QPushButton:checked { background-color: #1e90ff; }
        QPushButton:disabled { background-color: gray; color: #cccccc;}

        QSlider::groove:horizontal { height: 12px; background: #DCDCDC; border-radius: 6px; }
        QSlider::sub-page:horizontal { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #FDDFBA, stop:1 #FFA73C);  border-radius: 6px; }
        QSlider::handle:horizontal {
            width: 20px;
            height: 16px;
            margin: -6px 0;
            border-radius: 12px;
            background: white;
            border: 2px solid #FFB459; }

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

        QRadioButton { spacing: 5px; color: #333333; }
        QRadioButton::indicator {
            width: 14px;
            height: 14px;
            border: 2px solid #999999;
            border-radius: 8px; }

        QRadioButton::indicator:unchecked { background: #f8f8f8; }
        QRadioButton::indicator:unchecked:hover { border-color: #666666; background: #f0f0f0; }

        QRadioButton::indicator:checked {
            border: 2px solid #0085FF;
            background: qradialgradient(
                cx:0.5, cy:0.5, radius:0.4,
                fx:0.5, fy:0.5,
                stop:0 #0085FF, stop:1 white
            );
            color: #0085FF;
        }

        QRadioButton::indicator:checked:hover {
            border-color: #0066CC;
            background: qradialgradient(
                cx:0.5, cy:0.5, radius:0.4,
                fx:0.5, fy:0.5,
                stop:0 #0066CC, stop:1 white
            );
        }

        QRadioButton::indicator:pressed { border-color: #004499; }
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
            padding: 2px 2px;
        }


    QScrollBar:vertical,
    QScrollBar:horizontal {
        background: transparent;
        border: none;
        margin: 0px;
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
        background: rgba(160, 160, 160, 0);
        border-radius: 0px;
        border: 1px solid rgba(255, 255, 255, 0);
        min-height: 20px;
        min-width: 20px;
    }

    QScrollBar:vertical:hover QScrollBar::handle:vertical,
    QScrollBar:horizontal:hover QScrollBar::handle:horizontal {
        background: rgba(160, 160, 160, 0.5);
        border: 1px solid rgba(255, 255, 255, 0.2);
    }

    QScrollBar::handle:vertical:pressed,
    QScrollBar::handle:horizontal:pressed {
        background: rgba(120, 220, 120, 0.8);
    }

QScrollBar:vertical:hover {
    background: rgba(40, 240, 40, 1.0);
}
QScrollBar:horizontal:hover {
    background: rgba(240, 240, 240, 0.3);
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

QScrollBar::add-page:vertical,
QScrollBar::add-page:horizontal {background: #626262;}
QScrollBar::sub-page:vertical,
QScrollBar::sub-page:horizontal { background: #D9D9D9;}

    )");

    return a.exec();
}
