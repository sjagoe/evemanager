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


## Set the version number
VERSION = 1.3.1

## For testing, uncomment this line:
CONFIG += console

       
TEMPLATE = lib    # Dynamic library
CONFIG += dll     #
QT -= gui         # No need for GUI
QT += network xml # need Network and XML functionality to fetch the data
TARGET = EVE_API_Qt

DEPENDPATH += . include src
INCLUDEPATH += . include

DEFINES += _REENTRANT

CONFIG += thread
CONFIG += rtti
CONFIG += debug_and_release
# CONFIG(debug, debug|release)
# {
#     DESTDIR = ../bin/debug
# } else {
#     DESTDIR = ../bin/release
# }
DESTDIR = ../bin

# Input

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
