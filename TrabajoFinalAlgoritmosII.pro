#-------------------------------------------------
#
# Project created by QtCreator 2016-03-01T15:29:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TrabajoFinalAlgoritmosII
TEMPLATE = app


SOURCES += main.cpp\
        menuprincipal.cpp \
    juego.cpp \
    ficha.cpp \
    tablero.cpp \
    celda.cpp

HEADERS  += menuprincipal.h \
    juego.h \
    ficha.h \
    tablero.h \
    celda.h

FORMS    += menuprincipal.ui \
    juego.ui

RESOURCES += \
    iconos.qrc
