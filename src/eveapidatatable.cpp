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
