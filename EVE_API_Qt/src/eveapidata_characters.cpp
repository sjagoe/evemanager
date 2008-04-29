
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

#include "eveapidata_characters.hh"

/*!
Construct a character
*/
EveApiDataCharacter::EveApiDataCharacter( QString& name, QString& corpName,
        QString& charId, QString& corpId ) :
        _name( name ),
        _corpName( corpName ),
        _charId( charId ),
        _corpId( corpId )
{

}

/*!
return the charName
*/
const QString& EveApiDataCharacter::name()
{
    return this->_name;
}

/*!
return the corp name
*/
const QString& EveApiDataCharacter::corpName()
{
    return this->_corpName;
}

/*!
return the charId
*/
const QString& EveApiDataCharacter::charId()
{
    return this->_charId;
}

/*!
return the corpId
*/
const QString& EveApiDataCharacter::corpId()
{
    return this->_corpId;
}

/*!
construct the data container for account balance
*/
EveApiDataCharacters::EveApiDataCharacters() :
        EveApiData( PDT_CHARACTERLIST )
{

}

/*!
Add character
*/
void EveApiDataCharacters::addCharacter( QString& name, QString& corpName,
        QString& charId,
        QString& corpId )
{
    EveApiDataCharacter newChar( name, corpName, charId, corpId );

    this->_characters.append( newChar );
}

/*!
get all characters
*/
const QList<EveApiDataCharacter>& EveApiDataCharacters::getCharacters()
{
    return this->_characters;
}
