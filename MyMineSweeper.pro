#-------------------------------------------------
#
# Project created by QtCreator 2012-07-19T15:04:51
#
#-------------------------------------------------

QT       += core gui

TARGET = MyMineSweeper
TEMPLATE = app


SOURCES += main.cpp\
        cmine.cpp \
    mylabel.cpp \
    cmap.cpp \
    mylabelex.cpp \
    mydlg.cpp \
    crecord.cpp

HEADERS  += cmine.h \
    const.h \
    mylabel.h \
    cmap.h \
    mylabelex.h \
    mydlg.h \
    crecord.h

RESOURCES = image.qrc
	
FORMS    += cmine.ui
