# Copyright 2009 Simon Jagoe
# .
# This file is part of EVE_API_Qt.
# .
# EVE_API_Qt is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# .
# EVE_API_Qt is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
# .
# You should have received a copy of the GNU General Public License
# along with EVE_API_Qt. If not, see <http://www.gnu.org/licenses/>.
# .
QT += testlib \
    xmlpatterns
QT -= gui
TARGET = EVE_API_Parser_test
DESTDIR = ../../../bin
LIBS += -L../../../bin \
    -lEVE_API_Parser_Qt0
INCLUDEPATH += . \
    ../../../EVE_API_Qt/EVE_API_Parser/include
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += charactersparser_test.cpp \
    main.cpp
HEADERS += charactersparser_test.h
