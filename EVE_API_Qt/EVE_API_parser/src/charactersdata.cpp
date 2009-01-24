
/*
 * Copyright 2009 Simon Jagoe
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

#include "charactersdata.h"

EveApi::CharactersData::CharactersData( const int& version,
                                        const QDateTime& currentTime,
                                        const QDateTime& cachedUntil,
                                        Rowset<void*>* rowset ):
AbstractData(version, currentTime, cachedUntil)
{
    this->_characters = rowset;
}

EveApi::CharactersData::~CharactersData()
{
    if (this->_characters != 0)
        delete this->_characters;
}

QMap<QString, QString> EveApi::CharactersData::getCharacterNames()
{
    QMap<QString, QString> values;
    QString keyColumn = this->_characters->getKey();
    Row<void*>* row;
    foreach (row, this->_characters->rowsInOrder())
    {
        QString key = (*row)[keyColumn];
        QString column = "name";
        values.insert(column, (*row)[column]);
    }
    return values;
}

QMap<QString, QMap<QString, QString> > EveApi::CharactersData::getCharacters()
{
    QMap<QString, QMap<QString, QString> > values;
    QString keyColumn = this->_characters->getKey();
    Row<void*>* row;
    foreach (row, this->_characters->rowsInOrder())
    {
        QString key = (*row)[keyColumn];
        QMap<QString, QString> characterValues;
        foreach (const QString& column, this->_characters->getColumns())
        {
            characterValues.insert(column, (*row)[column]);
        }
        values.insert(key, characterValues);
    }
    return values;
}
