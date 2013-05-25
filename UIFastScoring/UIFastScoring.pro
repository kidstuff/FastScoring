#-------------------------------------------------
#
# Project created by QtCreator 2013-05-25T19:27:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UIFastScoring
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    processwidget.cpp

HEADERS  += mainwindow.h \
    processwidget.h

FORMS    += mainwindow.ui \
    processwidget.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ServiceClient/release/ -lServiceClient
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ServiceClient/debug/ -lServiceClient
else:unix:!symbian: LIBS += -L$$OUT_PWD/../ServiceClient/ -lServiceClient

INCLUDEPATH += $$PWD/../ServiceClient
DEPENDPATH += $$PWD/../ServiceClient

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DigitExtracter/release/ -lDigitExtracter
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DigitExtracter/debug/ -lDigitExtracter
else:unix:!symbian: LIBS += -L$$OUT_PWD/../DigitExtracter/ -lDigitExtracter

INCLUDEPATH += $$PWD/../DigitExtracter
DEPENDPATH += $$PWD/../DigitExtracter

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../FormPrinter/release/ -lFormPrinter
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../FormPrinter/debug/ -lFormPrinter
else:symbian: LIBS += -lFormPrinter
else:unix: LIBS += -L$$OUT_PWD/../FormPrinter/ -lFormPrinter

INCLUDEPATH += $$PWD/../FormPrinter
DEPENDPATH += $$PWD/../FormPrinter
