#include "eveapiwalker.hh"

//#include <Qt>
#include <QMetaType>
#include <QDateTime>

#include "eveapiwalkerthread.hh"

/*!
Simply call the QThread constructor. All data initialisation has to
happen in the run() method as we need an event loop.
*/
EveApiWalker::EveApiWalker( QObject* parent )
        : QThread( parent )
{
    qRegisterMetaType<QMap<int, QMap<QString, QString> > >( "QMap<int, QMap<QString, QString> >" );
    qRegisterMetaType<QDomDocument>( "QDomDocument" );
}

/*!
Add a new request to the queue to be processed when the current one is
complete

\return a newly generated unique identifier
*/
QString EveApiWalker::addRequest( QDomDocument doc )
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
Add a continuation request for journal walking

\return The same identifier as passed in the id parameter
*/
QString EveApiWalker::addRequest( QString id, QDomDocument doc )
{
    this->_requestSemaphore.release();
    if (this->_incompleteStorage.contains( id ))
    {
        QMap<int, QMap<QString, QString> > initial = this->_incompleteStorage.take( id );
        if (this->_requestSemaphore.available() == 1)
        {
            emit processPendingRequest( id, doc, initial );
        }
        else
        {
            this->_continuationQueue.enqueue( id );
            this->_continuationStorage.insert( id, qMakePair( initial, doc ) );
        }
        return id;
    }
    return QString();
}

/*!
Create the dynamic objects in the thread, and execute the event loop.
*/
void EveApiWalker::run()
{
    // create dynamic objects here
    this->_walker = new EveApiWalkerThread;

    // connect signals and slots
    // messages from the walker
    connect( this->_walker,
             SIGNAL( documentProcessed( QString, QMap<int, QMap<QString, QString> > ) ),
             this,
             SLOT( completeRequest( QString, QMap<int, QMap<QString, QString> > ) ) );
    connect( this->_walker,
             SIGNAL( incompleteDocument( QString, QMap<int, QMap<QString, QString> >, QPair<QString, QString> ) ),
             this,
             SLOT( queueIncompleteRequest( QString, QMap<int, QMap<QString, QString> >, QPair<QString, QString> ) ) );

    // messages to the walker
    connect( this, SIGNAL( processNewRequest( QString, QDomDocument ) ),
             this->_walker, SLOT( processRequest( QString, QDomDocument ) ) );
    connect( this,
             SIGNAL( processPendingRequest( QString, QDomDocument, QMap<int, QMap<QString, QString> > ) ),
             this->_walker,
             SLOT( processRequest( QString, QDomDocument, QMap<int, QMap<QString, QString> > ) ) );

    // start the thread's event loop
    this->exec();
}

/*!
create a unique identifier, using the object pointer "this", and the
current Date/Time, ensuring that all requests, across all instances of
the class have unique identifiers.
*/
QString EveApiWalker::makeID()
{
    QDateTime now = QDateTime::currentDateTime();
    int thisPtr = ( int ) this;
    QString id = QString( "%1::" ).arg( thisPtr, 0, 16 );
    id = id.append( now.toString() );
    return id;
}

/*!
Check if a request is queues, and if so, process it
*/
void EveApiWalker::checkQueue()
{
    if (!this->_continuationQueue.isEmpty())
    {
        QString id = this->_continuationQueue.dequeue();
        QPair<QMap<int, QMap<QString, QString> >, QDomDocument> req = this->_continuationStorage.take( id );
        emit processPendingRequest( id, req.second, req.first );
    }
    else if (!this->_requestQueue.isEmpty())
    {
        QString id = this->_requestQueue.dequeue();
        QDomDocument doc = this->_requestStorage.take( id );
        emit processNewRequest( id, doc );
    }
}

/*!
Slot that stores incomplete requests in a incomplete request queue
while the API fetches more data
*/
void EveApiWalker::queueIncompleteRequest( QString id,
        QMap<int, QMap<QString, QString> > processedDoc,
        QPair<QString, QString> beforeID )
{
    this->_requestSemaphore.tryAcquire();
    this->_incompleteStorage.insert( id, processedDoc );
    this->checkQueue();
    emit incompleteRequest( id, processedDoc, beforeID );
}

/*!
clean up after a completed request
*/
void EveApiWalker::completeRequest( QString id,
                                    QMap<int, QMap<QString, QString> > processedDoc )
{
    this->_requestSemaphore.tryAcquire();
    emit completedRequest( id, processedDoc );
}
