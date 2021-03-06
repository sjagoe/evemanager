
/*
 * Copyright 2007-2008 Simon Jagoe
 *
 * This file is part of EVE_API_Qt.
 *
 * EVE_API_Qt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EVE_API_Qt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EVE_API_Qt.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CHARACTERSPARSER_TEST_H
#define CHARACTERSPARSER_TEST_H

#include <QtTest/QtTest>

class CharactersParserTest: public QObject
{
    Q_OBJECT;
private slots:
    void parse_data();
    void parse();
    void charactersDataEquality_data();
    void charactersDataEquality();
    void charactersDataInequality_data();
    void charactersDataInequality();
};

#endif // CHARACTERSPARSER_TEST_H
