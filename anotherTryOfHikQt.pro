QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

win32{
    LIBS += $$PWD/libWin/HCCore.lib
    LIBS += $$PWD/libWin/HCNetSDK.lib
    LIBS += $$PWD/libWin/PlayCtrl.lib
    LIBS += $$PWD/libWin/GdiPlus.lib
    #LIBS += $$PWD/lib/HCAlarm.lib
    #LIBS += $$PWD/lib/HCGeneralCfgMgr.lib
    #LIBS += $$PWD/lib/HCPreview.lib

    INCLUDEPATH += $$PWD/includeWin
}

unix{
    #LIBS += -L$$PWD/libLin -lhcnetsdk -lPlayCtrl -lAudioRender -lSuperRender -lHCCore
LIBS += -LlibLin -Wl,-rpath=./:./HCNetSDKCom:/libLin -lhcnetsdk -lPlayCtrl -lAudioRender -lSuperRender


    INCLUDEPATH += $$PWD/includeLin
}




CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#unix:!macx: LIBS += -L$$PWD/libLin/ -lHCCore

INCLUDEPATH += $$PWD/includeLin
DEPENDPATH += $$PWD/includeLin
