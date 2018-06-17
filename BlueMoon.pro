# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------

TEMPLATE = app
TARGET = BlueMoon
DESTDIR = ./x64/Debug
QT += core network gui multimedia widgets
CONFIG += debug
DEFINES += _UNICODE WIN64 QT_DLL QT_MULTIMEDIA_LIB QT_NETWORK_LIB QT_WIDGETS_LIB
INCLUDEPATH += ./GeneratedFiles \
    . \
    ./GeneratedFiles/$(ConfigurationName) \
    ./ui \
    ./logic
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/$(ConfigurationName)
OBJECTS_DIR += debug
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
include(BlueMoon.pri)
win32:RC_FILE = BlueMoon.rc
