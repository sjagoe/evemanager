#include <QDomDocument>

#include <QStringList>
#include <QDate>
#include <QTime>

#include "eveapiparserthread.hh"

//! set up the parser
EveApiParserThread::EveApiParserThread( ParsedDataType thisType, QObject* parent ) :
    QObject( parent ),
    _type( thisType )
{

}

/*!
return the parser type
*/
const ParsedDataType& EveApiParserThread::type() const
{
    return this->_type;
}

/*!
Start the parser
*/
void EveApiParserThread::parse( QString parserId, shared_ptr<QDomDocument> doc )
{
    this->_parserMutex.lock();
    this->doParse( parserId, doc );
    this->_parserMutex.unlock();
}

/*!
getTime
*/
QDateTime EveApiParserThread::apiDateTimeToQDateTime( QString& apiDateTime )
{
    QStringList dateAndTime = apiDateTime.split( " " );
    QStringList dateStrings = dateAndTime.at( 0 ).split( "-" );
    QStringList timeStrings = dateAndTime.at( 1 ).split( ":" );

    int year = dateStrings.at( 0 ).toInt();
    int month = dateStrings.at( 1 ).toInt();
    int day = dateStrings.at( 2 ).toInt();

    int hours = timeStrings.at( 0 ).toInt();
    int minutes = timeStrings.at( 1 ).toInt();
    int seconds = timeStrings.at( 2 ).toInt();

    QDate date( year, month, day );
    QTime time( hours, minutes, seconds );

    QDateTime dateTime( date, time, Qt::UTC );

    return dateTime;
}
