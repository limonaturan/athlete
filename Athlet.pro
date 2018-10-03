#-------------------------------------------------
#
# Project created by QtCreator 2018-09-21T23:11:28
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Athlet
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    userdialog.cpp \
    usersettings.cpp \
    trainingheadertile.cpp \
    training.cpp \
    pugi/pugixml.cpp \
    trainingheaderswidget.cpp \
    trainingheaderscrollarea.cpp \
    centralwidget.cpp \
    trainingtabs.cpp \
    trainingmanager.cpp \
    plotspeeddistance.cpp \
    worldrecord.cpp \
    sqlhelper.cpp \
    plotdata.cpp \
    data.cpp \
    tabspeed.cpp \
    worldrecords.cpp \
    messageagent.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    simpledata.h \
    userdialog.h \
    usersettings.h \
    trainingheadertile.h \
    training.h \
    pugi/pugixml.hpp \
    trainingheaderswidget.h \
    trainingheaderscrollarea.h \
    centralwidget.h \
    trainingtabs.h \
    trainingmanager.h \
    plotspeeddistance.h \
    worldrecord.h \
    sqlhelper.h \
    plotdata.h \
    data.h \
    tabspeed.h \
    worldrecords.h \
    messageagent.h

FORMS    += mainwindow.ui
