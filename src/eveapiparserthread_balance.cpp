#include "eveapiparserthread_balance.hh"

#include <QMetaType>
#include <QDomNode>
#include <QDomElement>

/*!
Construct the parser
*/
EveApiParserThreadBalance::EveApiParserThreadBalance( QObject* parent ) :
    EveApiParserThread( PDT_ACCOUNTBALANCE, parent )
{
    qRegisterMetaType<EveApiDataBalance>("EveApiDataBalance");
}

/*!
Perform the actual parsing of the data, and emit a signal when done.
The signal must be defined in the subclass
*/
void EveApiParserThreadBalance::doParse( const QString& parserId, const QDomDocument& doc )
{
    EveApiDataBalance parsedData;
    // do parsing here
    emit parsingComplete( parserId, parsedData );
}
