#-------------------------------------------------
#
# Project created by QtCreator 2017-12-05T11:02:57
#
#-------------------------------------------------

QT       += core gui
QT += widgets multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageWithLabelTools
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
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
    imgprocthread.cpp \
    musicplayer.cpp

HEADERS += \
        mainwindow.h \
    imgprocthread.h \
    musicplayer.h

FORMS += \
        mainwindow.ui \
    musicplayer.ui

INCLUDEPATH += F:/opencvmingw/include
INCLUDEPATH += F:/opencvmingw/include/opencv
INCLUDEPATH += F:/opencvmingw/include/opencv2
DEPENDPATH += F:/opencvmingw/include
win32: LIBS += -LF:/opencvmingw/lib/ -llibopencv_core320.dll
win32: LIBS += -LF:/opencvmingw/lib/ -llibopencv_highgui320.dll
win32: LIBS += -LF:/opencvmingw/lib/ -llibopencv_imgproc320.dll
win32: LIBS += -LF:/opencvmingw/lib/ -llibopencv_features2d320.dll
win32: LIBS += -LF:/opencvmingw/lib/ -llibopencv_imgcodecs320.dll

