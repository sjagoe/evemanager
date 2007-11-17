#include "eveapiparserwalker.hh"

#include "eveapiparserwalkerthread.hh"

EveApiParserWalker::EveApiParserWalker( QObject* parent )
    : EveApiParser( new EveApiParserWalkerThread, parent )
{

}

/*!
Add a continuation request for journal walking

\return The same identifier as passed in the id parameter
*/
QString EveApiParserWalker::addRequest( QString id, QDomDocument doc )
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
Allow the continuation queue to be checked in subclasses that use it
*/
void EveApiParserWalker::checkContinuationQueue()
{
    QString id = this->_continuationQueue.dequeue();
    QPair<QMap<int, QMap<QString, QString> >, QDomDocument> req = this->_continuationStorage.take( id );
    emit processPendingRequest( id, req.second, req.first );
}

/*!
Method to be implemented by subclasses to connect signals and slots
(as the return types from the parser will differ in each case, and
cannot be defined generally here)
*/
void EveApiParserWalker::setup()
{
    // messages from the walker
    connect( &this->parser(),
             SIGNAL( documentProcessed( QString, QMap<int, QMap<QString, QString> > ) ),
             this,
             SLOT( completeRequest( QString, QMap<int, QMap<QString, QString> > ) ) );
    connect( &this->parser(),
             SIGNAL( incompleteDocument( QString, QMap<int, QMap<QString, QString> >, QPair<QString, QString> ) ),
             this,
             SLOT( queueIncompleteRequest( QString, QMap<int, QMap<QString, QString> >, QPair<QString, QString> ) ) );

    // messages to the walker
    connect( this,
             SIGNAL( processPendingRequest( QString, QDomDocument, QMap<int, QMap<QString, QString> > ) ),
             &this->parser(),
             SLOT( processRequest( QString, QDomDocument, QMap<int, QMap<QString, QString> > ) ) );
}

/*!
Slot that stores incomplete requests in a incomplete request queue
while the API fetches more data
*/
void EveApiParserWalker::queueIncompleteRequest( QString id,
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
void EveApiParserWalker::completeRequest( QString id,
                                    QMap<int, QMap<QString, QString> > processedDoc )
{
    this->_requestSemaphore.tryAcquire();
    this->checkQueue();
    emit completedRequest( id, processedDoc );
}
