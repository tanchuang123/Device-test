#-------------------------------------------------
#
# Project created by QtCreator 2018-03-19T15:43:19
#
#-------------------------------------------------

QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#LIBS     +=-LF:/work/WORK/qudong/libCan/lib/-IControlCAN
#INCLUDEPATH+=F:/work/WORK/qudong/libCan/lib/

TARGET = libCan
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    ControlCanDll.cpp \
    message/messagedialog.cpp \
    ConFiguration.cpp \
    RobotUdp/RobotUdp.cpp \
    RobotUdp/Widget_UDP.cpp \
    CanFrame/HelpByteArray.cpp \
    ControlCanDllForm.cpp \
    parameter_configform.cpp

HEADERS += \
        mainwindow.h \
    lib/ControlCAN.h \
    ControlCanDll.h \
    message/messagedialog.h \
    ConFiguration.h \
    RobotUdp/RobotUdp.h \
    RobotUdp/Widget_UDP.h \
    CanFrame/HelpByteArray.h \
    ControlCanDllForm.h \
    parameter_configform.h

FORMS += \
        mainwindow.ui \
    message/messagedialog.ui \
    ConFiguration.ui \
    RobotUdp/Widget_UDP.ui \
    ControlCanDllForm.ui \
    parameter_configform.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lControlCAN
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lControlCAN
else:unix: LIBS += -L$$PWD/lib/ -lControlCAN

INCLUDEPATH += $$PWD/lib
DEPENDPATH += $$PWD/lib
