#include "eveapiparseraccount.hh"

#include "eveapiaccount.hh"

#include "eveapiparserthread_characters.hh"

/*!
call QThread constructor
*/
EveApiParserAccount::EveApiParserAccount( QString& host, QString& dataPath,
        int& xmlIndent, QString& scope, QObject* parent ) :
        QThread( parent )
{
    this->_eveApi.reset( new EveApiAccount( host, dataPath, xmlIndent, scope ) );
    connect( this->_eveApi.get(), SIGNAL( requestComplete( QString, shared_ptr<QDomDocument>, QString, QDateTime ) ),
             this, SLOT( apiRequestComplete( QString, shared_ptr<QDomDocument>, QString, QDateTime ) ) );
    connect( this->_eveApi.get(), SIGNAL( requestFailed( QString, QString, QString ) ),
             this, SIGNAL( requestFailed( QString, QString, QString ) ) );
}

/*!
create a new request for the account balance
*/
QString EveApiParserAccount::characters( QMap<QString, QString>& parameters )
{
    this->_apiMutex.lock();
    // create an API request
    QString requestId = this->_eveApi->characters( parameters );
    // map the ID to a parser
    this->_requestIdToParserMap.insert( requestId, PDT_CHARACTERLIST );
    this->_apiMutex.unlock();
    return requestId;
}

/*!
create actual parser objects, and start the event loop
*/
void EveApiParserAccount::run()
{
    this->setupParsers();
    this->exec();
}

/*!
Create and set up the parsers
*/
void EveApiParserAccount::setupParsers()
{
    // AccountBalance Parser
//    shared_ptr<EveApiParserThread> parser( new EveApiParserThreadBalance );
//    connect( this, SIGNAL( parseAccountBalance( QString, shared_ptr<QDomDocument> ) ),
//             parser.get(), SLOT( parse( QString, shared_ptr<QDomDocument> ) ) );
//    connect( parser.get(), SIGNAL( parsingComplete( QString, shared_ptr<EveApiDataBalance> ) ),
//             this, SIGNAL( accountBalanceComplete( QString, shared_ptr<EveApiDataBalance> ) ) );
//    connect( parser.get(), SIGNAL( requestFailed( QString, QString, QString ) ),
//             this, SIGNAL( requestFailed( QString, QString, QString ) ) );
//    this->_parsers.insert( PDT_ACCOUNTBALANCE, parser );
}

/*!
API request is complete (i.e. the XML has been received from the API
*/
void EveApiParserAccount::apiRequestComplete( QString requestId,
        shared_ptr<QDomDocument> xmlDocument,
        QString httpResponse,
        QDateTime cacheExpireTime )
{
    ParsedDataType type = this->_requestIdToParserMap.take( requestId );
    switch ( type )
    {
        case PDT_CHARACTERLIST:
        {
            emit parseCharacters( requestId, xmlDocument );
            break;
        }
        default:
        {
            // invalid type for this request mechanism
            break;
        }
    }
}


