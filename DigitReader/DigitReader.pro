TEMPLATE = lib
CONFIG += console
QT += core

SOURCES += \
    digitreader.cpp

HEADERS += \
    digitreader.h

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv

