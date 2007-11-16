######################################################################
# Automatically generated by qmake (2.01a) Wed 14. Nov 20:34:58 2007
######################################################################

## Uncomment the second line to build the test app
## Comment the second line to build the library
## The first line can be left uncommented in both cases
## Note that the app requires the lib built as a dll (or .so)
TEMPLATE = lib
#TEMPLATE = app

contains( TEMPLATE, app ) {
    HEADERS += include/main.hh
    SOURCES += src/main.cpp
    LIBS += -Lbin/release -lEVE_API_Qt
}

contains ( TEMPLATE, lib ) {
    CONFIG += dll
    QT -= gui

    HEADERS += include/eveapi.hh \
               include/eveapirequest.hh \
               include/eveapigeneralrequest.hh \
               include/eveapicharacterrequest.hh \
               include/eveapiscope.hh \
               include/eveapieve.hh \
               include/eveapimap.hh \
               include/eveapicharacter.hh \
               include/eveapicorporation.hh \
               include/eveapiwalker.hh \
               include/eveapiwalkerthread.hh

    SOURCES += src/eveapi.cpp \
               src/eveapirequest.cpp \
               src/eveapigeneralrequest.cpp \
               src/eveapicharacterrequest.cpp \
               src/eveapiscope.cpp \
               src/eveapieve.cpp \
               src/eveapimap.cpp \
               src/eveapicharacter.cpp \
               src/eveapicorporation.cpp \
               src/eveapiwalker.cpp \
               src/eveapiwalkerthread.cpp
}

VERSION = 1.2.0
TARGET = EVE_API_Qt

DEPENDPATH += . include src
INCLUDEPATH += . include

QT += network xml

CONFIG += thread
CONFIG += debug_and_release
CONFIG(debug, debug|release)
{
    DESTDIR = bin/debug
} else {
    DESTDIR = bin/release
}

# Input

