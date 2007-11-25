#include <QDomDocument>

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
