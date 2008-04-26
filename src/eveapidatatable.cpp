
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

#include "eveapidatatable.hh"

/*!
Call default constructors
*/
EveApiDataTable::EveApiDataTable() :
    EveApiData(),
    _tableName(),
    _tableKey(),
    _tableColumns()
{

}

/*!
Create a table of a specific type
*/
EveApiDataTable::EveApiDataTable( ParsedDataType thisType ) :
    EveApiData( thisType ),
    _tableName(),
    _tableKey(),
    _tableColumns()
{

}

/*!
Get the table name
*/
const QString& EveApiDataTable::name() const
{
    return this->_tableName;
}

/*!
Set the table name
*/
void EveApiDataTable::setName( const QString& name )
{
    this->_tableName = name;
}

/*!
Get the table key
*/
const QString& EveApiDataTable::key() const
{
    return this->_tableKey;
}

/*!
Set the table key
*/
void EveApiDataTable::setKey( const QString& key )
{
    this->_tableKey = key;
}

/*!
Get the list of columns
*/
const QStringList& EveApiDataTable::columns() const
{
    return this->_tableColumns;
}

/*!
Set the list of columns
*/
void EveApiDataTable::setColumns( const QStringList& columns )
{
    this->_tableColumns = columns;
}
