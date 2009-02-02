
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

EveApi::CharacterData::CharacterData ( const QString& name, const QString& characterID,
                                       const QString& corporationName,
                                       const QString& corporationID ):
_name(name),
_characterID(characterID),
_corporationName(corporationName),
_corporationID(corporationID)
{
}

EveApi::CharacterData::CharacterData ( const CharacterData& other ):
_name(other.name()),
_characterID(other.characterID()),
_corporationName(other.corporationName()),
_corporationID(other.corporationID())
{
}

const QString& EveApi::CharacterData::name() const
{
    return this->_name;
}

const QString& EveApi::CharacterData::characterID() const
{
    return this->_characterID;
}

const QString& EveApi::CharacterData::corporationName() const
{
    return this->_corporationName;
}

const QString& EveApi::CharacterData::corporationID() const
{
    return this->_corporationID;
}

bool EveApi::CharacterData::operator==(const CharacterData& other) const
{
    if (this->_name == other.name() && this->_characterID == other.characterID()
        && this->_corporationName == other.corporationName()
        && this->_corporationID == other.corporationID())
        return true;
    return false;
}

bool EveApi::CharacterData::operator!=(const CharacterData& other) const
{
    return (! ((*this) == other));
}


EveApi::CharactersData::CharactersData( const int& version,
                                        const QDateTime& currentTime,
                                        const QDateTime& cachedUntil,
                                        const QList<CharacterData>& characters ):
AbstractData(version, currentTime, cachedUntil)
{
    this->_characters = characters;
}

EveApi::CharactersData::CharactersData( const CharactersData& other ):
        AbstractData(other.getVersion(), other.getServerTime(), other.getCachedUntilTime())
{
    this->_characters = other.characters();
}

QMap<QString, QString> EveApi::CharactersData::getCharacterNames()
{
    QMap<QString, QString> values;
    foreach (const CharacterData& character, this->_characters)
    {
        values.insert(character.characterID(), character.name());
    }
    return values;
}

QMap<QString, QMap<QString, QString> > EveApi::CharactersData::getCharacters()
{
    QMap<QString, QMap<QString, QString> > values;

    foreach (const CharacterData& character, this->_characters)
    {
        QMap<QString, QString> innerValues;
        innerValues.insert(QString("name"), character.name());
        innerValues.insert(QString("characterID"), character.characterID());
        innerValues.insert(QString("corporationName"), character.corporationName());
        innerValues.insert(QString("corporationID"), character.corporationID());
        values.insert(character.characterID(), innerValues);
    }
    return values;
}

const QList<EveApi::CharacterData>& EveApi::CharactersData::characters() const
{
    return this->_characters;
}

bool EveApi::CharactersData::operator==(const CharactersData& other) const
{
    return this->_characters == other.characters();
}

bool EveApi::CharactersData::operator!=(const CharactersData& other) const
{
    return this->_characters != other.characters();
}
