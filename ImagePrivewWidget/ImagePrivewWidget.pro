CONFIG      += designer plugin debug_and_release
TARGET      = $$qtLibraryTarget(imagepreviewwidgetplugin)
TEMPLATE    = lib

HEADERS     = imagepreviewwidgetplugin.h
SOURCES     = imagepreviewwidgetplugin.cpp
RESOURCES   = icons.qrc
LIBS        += -L. 

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(imagepreviewwidget.pri)
