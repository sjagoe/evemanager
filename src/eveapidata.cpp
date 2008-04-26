
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

#include "eveapidata.hh"

/*!
Call default constructors
*/
EveApiData::EveApiData() :
    _type( PDT_NULL ),
    _timeFetched(),
    _cachedUntil()
{

}

/*!
Create a datt container of a specific type
*/
EveApiData::EveApiData( ParsedDataType thisType ) :
    _type( thisType ),
    _timeFetched(),
    _cachedUntil()
{

}

const ParsedDataType& EveApiData::type() const
{
    return this->_type;
}

const QDateTime& EveApiData::timeFetched() const
{
    return this->_timeFetched;
}

/*!
Set the time fetched
*/
void EveApiData::setTimeFetched( const QDateTime& dateTime )
{
    this->_timeFetched = dateTime;
}

const QDateTime& EveApiData::cachedUntil() const
{
    return this->_cachedUntil;
}

/*!
Set the time that the cache expires
*/
void EveApiData::setCachedUntil( const QDateTime& dateTime )
{
    this->_cachedUntil = dateTime;
}
