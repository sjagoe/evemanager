#include "eveapiparserwalkerthread.hh"

EveApiParserWalkerThread::EveApiParserWalkerThread( QObject* parent )
    : EveApiParserThread( parent )
{

}

/*!
process a new request
*/
void EveApiParserWalkerThread::processRequest( QString id,
        QDomDocument doc )
{

}

/*!
continue processing an old request
*/
void EveApiParserWalkerThread::processRequest( QString id,
        QDomDocument doc,
        EveApiData processedDoc )
{
    //EveApiDataWalked b = (*(EveApiDataWalked*)(&processedDoc));
}

/*!
Provide the actual XML parsing functionality
*/
QPair<QString, QString> EveApiParserWalkerThread::processSegment( QDomDocument doc,
        EveApiDataWalked& processedDoc )
{
    return QPair<QString, QString>();
}
