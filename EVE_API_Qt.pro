# Copyright 2007-2008 Simon Jagoe
#
# This file is part of EVE_API_Qt.
#
# EVE_API_Qt is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# EVE_API_Qt is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with EVE_API_Qt.  If not, see <http://www.gnu.org/licenses/>.


# select the library/part to build
# Options are:
# base:     The base library that provides access to the API
#           Requires: None
# parser:   An interface to the API that also provides transaparent, asynchronous XML parsing
#           Requires: base
# base_app: A simple application that provides a GUI to test the base library
#           Requires: base
API_BUILD = base

## Set the version number
VERSION = 1.3.1

## For testing, uncomment this line:
CONFIG += console

## Uncomment the second line to build the test app
## Comment the second line to build the library
## The first line can be left uncommented in both cases
## Note that the app requires the lib built as a dll (or .so)
#TEMPLATE = lib
#TEMPLATE = app

# if base is selected, build the base api, and do not link to QtGui
contains ( API_BUILD, base ) {
    TEMPLATE = lib    # Dynamic library
    CONFIG += dll     #
    QT -= gui         # No need for GUI
    QT += network xml # need Network and XML functionality to fetch the data
    TARGET = EVE_API_Qt

    HEADERS += include/eveapi.hh \
               \
               include/eveapirequest.hh \
               include/eveapiaccountrequest.hh \
               include/eveapigeneralrequest.hh \
               include/eveapicharacterrequest.hh \
               \
               include/eveapiscope.hh \
               include/eveapiaccount.hh \
               include/eveapieve.hh \
               include/eveapimap.hh \
               include/eveapicommon.hh \
               include/eveapicharacter.hh \
               include/eveapicorporation.hh

    SOURCES += src/eveapi.cpp \
               \
               src/eveapirequest.cpp \
               src/eveapiaccountrequest.cpp \
               src/eveapigeneralrequest.cpp \
               src/eveapicharacterrequest.cpp \
               \
               src/eveapiscope.cpp \
               src/eveapiaccount.cpp \
               src/eveapieve.cpp \
               src/eveapimap.cpp \
               src/eveapicommon.cpp \
               src/eveapicharacter.cpp \
               src/eveapicorporation.cpp
}

# if the parser is selected, build the parser library, link to the api lib, and do not link to QtGui
contains( API_BUILD, parser ) {
    TEMPLATE = lib # The parser is a dynamic library
    CONFIG += dll  #
    QT -= gui      # does not need any GUI elements
    QT += xml      # uses the XML Qt elements
    TARGET = EVE_API_Parser_Qt
    LIBS += -Lbin/release -lEVE_API_Qt
    VERSION = 0.1.0

    HEADERS += include/eveapiparser.hh \
               \
               include/eveapiparseraccount.hh \
               include/eveapiparsereve.hh \
               include/eveapiparsermap.hh \
               include/eveapiparsercharacter.hh \
               include/eveapiparsercorporation.hh \
               \
               include/eveapiparserthread.hh \
               include/eveapiparserthread_characters.hh \
               include/eveapiparserthread_balance.hh \
               \
               include/eveapidatatype.hh \
               \
               include/eveapidata.hh \
               include/eveapidatatable.hh \
               include/eveapidata_characters.hh \
               include/eveapidata_walked.hh \
               include/eveapidata_balance.hh

    SOURCES += src/eveapiparser.cpp \
               \
               src/eveapiparseraccount.cpp \
               src/eveapiparsereve.cpp \
               src/eveapiparsermap.cpp \
               src/eveapiparsercharacter.cpp \
               src/eveapiparsercorporation.cpp \
               \
               src/eveapiparserthread.cpp \
               src/eveapiparserthread_characters.cpp \
               src/eveapiparserthread_balance.cpp \
               \
               src/eveapidata.cpp \
               src/eveapidatatable.cpp \
               src/eveapidata_characters.cpp \
               src/eveapidata_walked.cpp \
               src/eveapidata_balance.cpp
}

# if the test app is selected, build the EXE and link to the base API
contains( API_BUILD, base_app ) {
    TEMPLATE = app
    QT += xml
    HEADERS += include/main.hh
    SOURCES += src/main.cpp
    LIBS += -Lbin/release -lEVE_API_Qt
    TARGET = EVE_API_Qt_base_app
}

DEPENDPATH += . include src
INCLUDEPATH += . include

DEFINES += _REENTRANT

CONFIG += thread
CONFIG += rtti
CONFIG += debug_and_release
#CONFIG(debug, debug|release)
#{
#    DESTDIR = bin/debug
#} else {
#    DESTDIR = bin/release
#}
DESTDIR = bin/release

# Input

