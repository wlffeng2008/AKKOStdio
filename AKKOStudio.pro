QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

LIBS += -L$$PWD -lhidapi

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DESTDIR = ../../bin

INCLUDEPATH += ./Module

SOURCES += \
    ColorLabel.cpp \
    ColorSquare.cpp \
    DialogDeviceConnect.cpp \
    DialogMainwork.cpp \
    FrameAbout.cpp \
    FrameKeySetting.cpp \
    FrameLight.cpp \
    FrameMacro.cpp \
    FrameMagic.cpp \
    FrameMain.cpp \
    LinearFixing1.cpp \
    LinearFixing2.cpp \
    MacroSquare.cpp \
    Module/ColorSlider.cpp \
    Module/MacroItem.cpp \
    Module/ModuleDKSItem.cpp \
    Module/ModuleEfColor.cpp \
    Module/ModuleEfLumi.cpp \
    Module/ModuleEfMode.cpp \
    Module/ModuleEfSpeed.cpp \
    Module/ModuleLangMenu.cpp \
    Module/ModuleLinear.cpp \
    Module/ModuleRtSet.cpp \
    Module/ModuleKeyboard.cpp \
    Module/ModuleVideoItem.cpp \
    ModuleScrollValue.cpp \
    NewTabWidget.cpp \
    SuperLabel.cpp \
    ToggleButton.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    ColorLabel.h \
    ColorSquare.h \
    DialogDeviceConnect.h \
    DialogMainwork.h \
    FrameAbout.h \
    FrameKeySetting.h \
    FrameLight.h \
    FrameMacro.h \
    FrameMagic.h \
    FrameMain.h \
    LinearFixing1.h \
    LinearFixing2.h \
    MacroSquare.h \
    MainWindow.h \
    Module/ColorSlider.h \
    Module/MacroItem.h \
    Module/ModuleDKSItem.h \
    Module/ModuleEfColor.h \
    Module/ModuleEfLumi.h \
    Module/ModuleEfMode.h \
    Module/ModuleEfSpeed.h \
    Module/ModuleLangMenu.h \
    Module/ModuleLinear.h \
    Module/ModuleRtSet.h \
    Module/ModuleKeyboard.h \
    Module/ModuleVideoItem.h \
    ModuleScrollValue.h \
    NewTabWidget.h \
    SuperLabel.h \
    ToggleButton.h

FORMS += \
    DialogDeviceConnect.ui \
    DialogMainwork.ui \
    FrameAbout.ui \
    FrameKeySetting.ui \
    FrameLight.ui \
    FrameMacro.ui \
    FrameMagic.ui \
    FrameMain.ui \
    MainWindow.ui \
    Module/MacroItem.ui \
    Module/ModuleDKSItem.ui \
    Module/ModuleEfColor.ui \
    Module/ModuleEfLumi.ui \
    Module/ModuleEfMode.ui \
    Module/ModuleEfSpeed.ui \
    Module/ModuleLangMenu.ui \
    Module/ModuleLinear.ui \
    Module/ModuleRtSet.ui \
    Module/ModuleKeyboard.ui \
    Module/ModuleVideoItem.ui \
    ModuleScrollValue.ui

TRANSLATIONS += \
    AKKOStudio_en_US.ts \
    AKKOStudio_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
