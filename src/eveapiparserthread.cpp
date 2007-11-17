#include "eveapiparserthread.hh"

/*!
call the QObject constructor
*/
EveApiParserThread::EveApiParserThread( QObject* parent )
        : QObject( parent )
{

}

/*!
process a new request
*/
void EveApiParserThread::processRequest( QString id,
        QDomDocument doc )
{

}

/*!
continue processing an old request
*/
void EveApiParserThread::processRequest( QString id,
        QDomDocument doc,
        QMap<int, QMap<QString, QString> > processedDoc )
{

}

/*!
Provide the actual XML parsing functionality
*/
QPair<QString, QString> EveApiParserThread::processSegment( QDomDocument doc,
        QMap<int, QMap<QString, QString> >& processedDoc )
{
    return QPair<QString, QString>();
}
