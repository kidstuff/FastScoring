TEMPLATE = lib
CONFIG += console
QT += core

SOURCES += \
    digitextracter.cpp \
    pointdigitextracter.cpp \
    chardigitextracter.cpp

HEADERS += \
    digitextracter.h \
    pointdigitextracter.h \
    chardigitextracter.h \
    digitresult.h


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DigitReader/release/ -lDigitReader
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DigitReader/debug/ -lDigitReader
else:unix:!symbian: LIBS += -L$$OUT_PWD/../DigitReader/ -lDigitReader

INCLUDEPATH += $$PWD/../DigitReader
DEPENDPATH += $$PWD/../DigitReader

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv
