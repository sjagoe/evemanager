#include "eveapiwalkerthread.hh"

/*!
call the QObject constructor
*/
EveApiWalkerThread::EveApiWalkerThread( QObject* parent )
        : QObject( parent )
{

}

/*!
process a new request
*/
void EveApiWalkerThread::processRequest( QString id,
        QDomDocument doc )
{

}

/*!
continue processing an old request
*/
void EveApiWalkerThread::processRequest( QString id,
        QDomDocument doc,
        QMap<int, QMap<QString, QString> > processedDoc )
{

}

/*!
Provide the actual XML parsing functionality
*/
QPair<QString, QString> EveApiWalkerThread::processSegment( QDomDocument doc,
        QMap<int, QMap<QString, QString> >& processedDoc )
{

}
