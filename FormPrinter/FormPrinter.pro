TEMPLATE = lib
CONFIG += console
QT += core xml

greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

SOURCES += \
    formprinter.cpp


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ServiceClient/release/ -lServiceClient
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ServiceClient/debug/ -lServiceClient
else:symbian: LIBS += -lServiceClient
else:unix: LIBS += -L$$OUT_PWD/../ServiceClient/ -lServiceClient

INCLUDEPATH += $$PWD/../ServiceClient
DEPENDPATH += $$PWD/../ServiceClient

HEADERS += \
    formprinter.h
