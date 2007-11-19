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
