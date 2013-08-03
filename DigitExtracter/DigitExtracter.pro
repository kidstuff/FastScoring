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

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DigitReader/release/ -lDigitReader
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DigitReader/debug/ -lDigitReader
else:unix:!symbian: LIBS += -L$$OUT_PWD/../DigitReader/ -lDigitReader

INCLUDEPATH += $$PWD/../DigitReader
DEPENDPATH += $$PWD/../DigitReader


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ServiceClient/release/ -lServiceClient
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ServiceClient/debug/ -lServiceClient
else:unix: LIBS += -L$$OUT_PWD/../ServiceClient/ -lServiceClient

INCLUDEPATH += $$PWD/../ServiceClient
DEPENDPATH += $$PWD/../ServiceClient
