#include "eveapiparser.hh"

//#include <Qt>
#include <QMetaType>
#include <QDateTime>

#include "eveapiparserwalkerthread.hh"

/*!
Simply call the QThread constructor. All data initialisation has to
happen in the run() method as we need an event loop.
*/
EveApiParser::EveApiParser( /*EveApiParserThread* newParser,*/ QObject* parent )
        : QThread( parent )
{
    qRegisterMetaType<EveApiData>("EveApiData");
    qRegisterMetaType<QDomDocument>( "QDomDocument" );
}

/*!
Destructor to clean up afterwards
*/
EveApiParser::~EveApiParser()
{
    //delete this->_parser;
}

/*!
Add a new request to the queue to be processed when the current one is
complete

\return a newly generated unique identifier
*/
QString EveApiParser::addRequest( ParsedDataType parserType, QDomDocument doc )
{
    QString parserId;
    EveApiParserThread* parser = this->_parsers.value( parserType );
    if (parser)
    {
        this->_requestSemaphore.release();
        parserId = makeParserID();
        connect( this,
                 SIGNAL( processNewRequest( QString, QDomDocument ) ),
                 parser,
                 SLOT( processRequest( QString, QDomDocument ) ) );
        if (this->_requestSemaphore.available() == 1)
        {
            emit processNewRequest( parserId, doc );
        }
        else
        {
            this->_requestQueue.enqueue(parserId);
            this->_requestStorage.insert( parserId, doc );
        }
        disconnect( this,
                 SIGNAL( processNewRequest( QString, QDomDocument ) ),
                 parser,
                 SLOT( processRequest( QString, QDomDocument ) ) );
        parser = 0;
    }
    return parserId;
}

/*!
Add a continuation request for journal walking

\return The same identifier as passed in the id parameter
*/
QString EveApiParser::addRequest( ParsedDataType parserType, QString parserId, QDomDocument doc )
{
    QString parserId1;
    EveApiParserThread* parser = this->_parsers.value( parserType );
    if (parser)
    {
        this->_requestSemaphore.release();
        connect( this,
             SIGNAL( processPendingRequest( QString, QDomDocument, EveApiData ) ),
             parser,
             SLOT( processRequest( QString, QDomDocument, EveApiData ) ) );
        if (this->_incompleteStorage.contains( parserId ))
        {
            EveApiData initial = this->_incompleteStorage.take( parserId );
            if (this->_requestSemaphore.available() == 1)
            {
                emit processPendingRequest( parserId, doc, initial );
            }
            else
            {
                this->_continuationQueue.enqueue( parserId );
                this->_continuationStorage.insert( parserId, qMakePair( initial, doc ) );
            }
            //return parserId;
            parserId1 = parserId;
        }
        disconnect( this,
             SIGNAL( processPendingRequest( QString, QDomDocument, EveApiData ) ),
             parser,
             SLOT( processRequest( QString, QDomDocument, EveApiData ) ) );
    }
    return parserId1;
}

/*!
Create the dynamic objects in the thread, and execute the event loop.
*/
void EveApiParser::run()
{
    // create dynamic objects and connect signals and slots
    this->setup();

    // start the thread's event loop
    this->exec();
}

/*!
Check if a request is queues, and if so, process it
*/
void EveApiParser::checkQueue()
{
    if (!this->_continuationQueue.isEmpty())
    {
//        this->checkContinuationQueue();
        QString parserId = this->_continuationQueue.dequeue();
        QPair<EveApiData, QDomDocument> req = this->_continuationStorage.take( parserId );
        emit processPendingRequest( parserId, req.second, req.first );
    }
    else if (!this->_requestQueue.isEmpty())
    {
        QString parserId = this->_requestQueue.dequeue();
        QDomDocument doc = this->_requestStorage.take( parserId );
        emit processNewRequest( parserId, doc );
    }
}

///*!
//Allow the continuation queue to be checked in subclasses that use it
//*/
//void EveApiParser::checkContinuationQueue()
//{
//    QString parserId = this->_continuationQueue.dequeue();
//    QPair<EveApiData, QDomDocument> req = this->_continuationStorage.take( parserId );
//    emit processPendingRequest( parserId, req.second, req.first );
//}

void EveApiParser::setup()
{
    EveApiParserThread* newParser = new EveApiParserWalkerThread;
    this->_parsers.insert( PDT_WALKED, newParser );
    //specific
    connect( newParser,
             SIGNAL( incompleteDocument( QString, EveApiData, QPair<QString, QString> ) ),
             this,
             SLOT( queueIncompleteRequest( QString, EveApiData, QPair<QString, QString> ) ) );

    // general
    EveApiParserThread* parser = 0;
    foreach( parser, this->_parsers )
    {
        connect( parser,
                 SIGNAL( documentProcessed( QString, EveApiData ) ),
                 this,
                 SLOT( completeRequest( QString, EveApiData ) ) );
    }
}

/*!
create a unique identifier, using the object pointer "this", and the
current Date/Time, ensuring that all requests, across all instances of
the class have unique identifiers.
*/
QString EveApiParser::makeParserID()
{
    QDateTime now = QDateTime::currentDateTime();
    int thisPtr = ( int ) this;
    QString parserId = now.toString("yyyyMMddhhmmsszzz");
    parserId = parserId.append( QString( "-%1-" ).arg( thisPtr, 0, 16 ) );
    parserId = parserId.append( QString( "%1" ).arg( this->_requestSemaphore.available() ) );
    return parserId;
}

/*!
Slot that stores incomplete requests in a incomplete request queue
while the API fetches more data
*/
void EveApiParser::queueIncompleteRequest( QString parserId,
                             EveApiData processedDoc,
                             QPair<QString, QString> beforeID )
{
    this->_requestSemaphore.tryAcquire();
    this->_incompleteStorage.insert( parserId, processedDoc );
    this->checkQueue();
    emit incompleteRequest( parserId, processedDoc, beforeID );
}

/*!
clean up after a completed request
*/
void EveApiParser::completeRequest( QString parserId,
                      EveApiData processedDoc )
{
    this->_requestSemaphore.tryAcquire();
    this->checkQueue();
    emit completedRequest( parserId, processedDoc );
}

