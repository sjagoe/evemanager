#include "eveapiparser.hh"

//#include <Qt>
#include <QMetaType>
#include <QDateTime>


/*!
Simply call the QThread constructor. All data initialisation has to
happen in the run() method as we need an event loop.
*/
EveApiParser::EveApiParser( EveApiParserThread* newParser, QObject* parent )
        : QThread( parent )
{
    qRegisterMetaType<QMap<int, QMap<QString, QString> > >( "QMap<int, QMap<QString, QString> >" );
    qRegisterMetaType<QDomDocument>( "QDomDocument" );
    this->_parser = newParser;
}

/*!
Add a new request to the queue to be processed when the current one is
complete

\return a newly generated unique identifier
*/
QString EveApiParser::addRequest( QDomDocument doc )
{
    this->_requestSemaphore.release();
    QString id = makeID();
    if (this->_requestSemaphore.available() == 1)
    {
        emit processNewRequest( id, doc );
    }
    else
    {
        this->_requestQueue.enqueue(id);
        this->_requestStorage.insert( id, doc );
    }
    return id;
}

/*!
Allow access to the parser without the ability to modify it
*/
EveApiParserThread& EveApiParser::parser()
{
    return (*this->_parser);
}

/*!
Create the dynamic objects in the thread, and execute the event loop.
*/
void EveApiParser::run()
{
    // create dynamic objects here
    this->_parser->moveToThread(this);

    // connect signals and slots
    connect( this, SIGNAL( processNewRequest( QString, QDomDocument ) ),
             this->_parser, SLOT( processRequest( QString, QDomDocument ) ) );
    // connect parser-specific signals and slots
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
        this->checkContinuationQueue();
    }
    else if (!this->_requestQueue.isEmpty())
    {
        QString id = this->_requestQueue.dequeue();
        QDomDocument doc = this->_requestStorage.take( id );
        emit processNewRequest( id, doc );
    }
}

/*!
create a unique identifier, using the object pointer "this", and the
current Date/Time, ensuring that all requests, across all instances of
the class have unique identifiers.
*/
QString EveApiParser::makeID()
{
    QDateTime now = QDateTime::currentDateTime();
    int thisPtr = ( int ) this;
    QString id = QString( "%1::" ).arg( thisPtr, 0, 16 );
    id = id.append( now.toString() );
    return id;
}


