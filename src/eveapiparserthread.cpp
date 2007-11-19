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
void EveApiParserThread::parse( const QString& parserId, const QDomDocument& doc )
{
//    this->_queueSize.release();
//    if ( this->_queueSize.available() > 1 )
//    {
//        this->_parserQueue.enqueue( qMakePair( parserId, doc ) );
//    }
//    else
//    {
        this->_parserMutex.lock();
        this->doParse( parserId, doc );
        this->_parserMutex.unlock();
//        this->_queueSize.tryAcquire();
//        if ( this->_queueSize.available() > 0 )
//        {
//            QPair<QString, QDomDocument> pair = this->_parserQueue.dequeue();
//            this->doParse( parserId, doc );
//        }
//    }
}
