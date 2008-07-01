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

VERSION = 1.4.0


TEMPLATE = app
QT += xml
LIBS += -L../bin -lEVE_API_Qt1
TARGET = EVE_API_Qt_base_app

DEPENDPATH += . include src
INCLUDEPATH += . include ../EVE_API/include

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

HEADERS += include/main.hh
SOURCES += src/main.cpp
