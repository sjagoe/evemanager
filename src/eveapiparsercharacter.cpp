#include "eveapiparsercharacter.hh"

#include "eveapicharacter.hh"

/*!
call QThread constructor
*/
EveApiParserCharacter::EveApiParserCharacter( QString& host, QString& dataPath,
            int& xmlIndent, QString& scope, QObject* parent ) :
    QThread( parent )
{
    this->_eveApi = new EveApiCharacter( host, dataPath, xmlIndent, scope );
}

/*!
create a new request for the account balance
*/
QString EveApiParserCharacter::accountBalance( QMap<QString, QString>& parameters )
{
    this->_apiMutex.lock();
    // create an API request
    QString requestId = this->_eveApi->accountBalance( parameters );
    // map the ID to a parser
    this->_requestIdToParserMap.insert( requestId, PDT_ACCOUNTBALANCE );
    this->_apiMutex.unlock();
    return requestId;
}

/*!
create actual parser objects, and start the event loop
*/
void EveApiParserCharacter::run()
{
    this->exec();
}
