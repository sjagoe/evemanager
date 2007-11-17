#include "eveapicharacter.hh"

#include "eveapicharacterrequest.hh"

#include "eveapiparserwalker.hh"

#include <QList>

/*!
create the child classes that provide API functionality
*/
EveApiCharacter::EveApiCharacter( QString& host, QString& dataPath, int& xmlIndent,
                                  QString& scope, QObject* parent )
        : EveApiScope( host, dataPath, xmlIndent, scope, parent )
{
#if !defined(EVEAPI_NO_PARSING)
    this->createParsers();
#endif
    this->createRequests();
}

/*!
access the CharacterSheet api function
*/
QString EveApiCharacter::characterSheet( QMap<QString, QString>& parameters )
{
    QString id = this->characterSheetRequestID();
    return this->request( id, parameters );
}

/*!
access the SkillInTraining api function
*/
QString EveApiCharacter::skillInTraining( QMap<QString, QString>& parameters )
{
    QString id = this->skillInTrainingRequestID();
    return this->request( id, parameters );
}

/*!
access the WalletJournal api function
*/
QString EveApiCharacter::walletJournal( QMap<QString, QString>& parameters )
{
    QString id = this->walletJournalRequestID();
    return this->request( id, parameters );
}

/*!
access the WalletTransactions api function
*/
QString EveApiCharacter::walletTransactions( QMap<QString, QString>& parameters )
{
    QString id = this->walletTransactionsRequestID();
    return this->request( id, parameters );
}

/*!
access the AccountBalance api function
*/
QString EveApiCharacter::accountBalance( QMap<QString, QString>& parameters )
{
    QString id = this->accountBalanceRequestID();
    return this->request( id, parameters );
}

#if !defined(EVEAPI_NO_PARSING)
/*!
access the WalletJournal api function, and provide a parse,
fully 'walked' output
*/
QString EveApiCharacter::walletJournalParsed( QMap<QString, QString>& parameters )
{
    QString id = this->walletJournalRequestID();
    this->_requestIdToParserMap.insert( id, this->_parserWalker );
    QString requestId = this->request( id, parameters, true );
    this->_requestIdToRequestMap.insert( requestId, id );
    this->_requestIdToRequestParametersMap.insert( requestId, parameters );
    return requestId;
}

/*!
This slot is called when an internal request is complete, so that it
can be parsed
*/
void EveApiCharacter::internalRequestComplete( QString requestId,
        QDomDocument result,
        QString httpResponse,
        QDateTime cacheTime )
{
    EveApiParser* parser = this->_requestIdToParserMap.value( requestId );
    if (parser)
    {
        QString parserId = this->_requestIdToParserIdMap.value( requestId );
        if (!parserId.isEmpty())
        {
            //parserId =
            QString newParserId = parser->addRequest( parserId, result );
        }
        else
        {
            parserId = parser->addRequest( result );
            this->_parserIdToRequestIdMap.insert( parserId, requestId );
            this->_requestIdToParserIdMap.insert( requestId, parserId );
        }
    }
}

/*!
Create all parsers
*/
void EveApiCharacter::createParsers()
{
    this->_parserWalker = new EveApiParserWalker;
//    /*!
//    continue processing a pending request (used internally to tell the
//    parser thread to begin with a new request)
//    */
//    void processPendingRequest( QString id,
//                                QDomDocument doc,
//                                QMap<int, QMap<QString, QString> > processedDoc );

//    /*!
//    notify the waiting object about the incomplete request
//    */
//    void incompleteRequest( QString id,
//                            QMap<int, QMap<QString, QString> > processedDoc,
//                            QPair<QString, QString> beforeID );

//    /*!
//    notify the waiting object about the complete request
//    */
//    void completedRequest( QString id,
//                          QMap<int, QMap<QString, QString> > processedDoc );
}
#endif

/*!
Create request objects
*/
void EveApiCharacter::createRequest( QString& requestId,
                                     QStringList& requiredParams,
                                     QStringList& optionalParams,
                                     QStringList& cacheId )
{
    EveApiRequest* newRequest = new EveApiCharacterRequest( requestId,
            this->dataPath(),
            this->xmlIndent(),
            requiredParams,
            optionalParams,
            cacheId );
    this->addRequestType( requestId, newRequest );
}

/*!
create all requests (delegated from the constructor)
*/
void EveApiCharacter::createRequests()
{
    QStringList requiredParams;
    QStringList optionalParams;
    QStringList cacheID;

    // CharacterSheet request
    requiredParams.clear();
    requiredParams << "userID" << "characterID" << "apiKey";
    optionalParams.clear();
    cacheID.clear();
    QString requestID = this->characterSheetRequestID();
    createRequest( requestID, requiredParams, optionalParams, cacheID );

    // SkillInTraining request
    requiredParams.clear();
    requiredParams << "userID" << "characterID" << "apiKey";
    optionalParams.clear();
    cacheID.clear();
    requestID = this->skillInTrainingRequestID();
    createRequest( requestID, requiredParams, optionalParams, cacheID );

    // AccountBalance request
    requiredParams.clear();
    requiredParams << "userID" << "characterID" << "apiKey";
    optionalParams.clear();
    cacheID.clear();
    requestID = this->accountBalanceRequestID();
    createRequest( requestID, requiredParams, optionalParams, cacheID );

    // WalletJournal request
    requiredParams.clear();
    requiredParams << "userID" << "characterID" << "apiKey";
    optionalParams.clear();
    optionalParams << "beforeRefID";
    cacheID.clear();
    cacheID << "beforeRefID";
    requestID = this->walletJournalRequestID();
    createRequest( requestID, requiredParams, optionalParams, cacheID );

    // WalletTransactions request
    requiredParams.clear();
    requiredParams << "userID" << "characterID" << "apiKey";
    optionalParams.clear();
    optionalParams << "beforeTransID";
    cacheID.clear();
    cacheID << "beforeTransID";
    requestID = this->walletTransactionsRequestID();
    createRequest( requestID, requiredParams, optionalParams, cacheID );
}

#if !defined(EVEAPI_NO_PARSING)
/*!
notify the waiting object about the incomplete request
*/
void EveApiCharacter::walkerRequestIncomplete( QString parserId,
                        EveApiDataWalked processedDoc,
                        QPair<QString, QString> beforeID )
{
    QString requestId = this->_parserIdToRequestIdMap.value( parserId );
    QMap<QString, QString> parameters = this->_requestIdToRequestParametersMap.value( requestId );
    if (!requestId.isNull())
    {
        QString req = this->_requestIdToRequestMap.value( requestId );
        if (!req.isNull())
        {
            parameters.insert( beforeID.first, beforeID.second );
            QString newRequestId = this->request( req, parameters, true, requestId );
        }
    }
}

/*!
notify the waiting object about the complete request
*/
void EveApiCharacter::walkerRequestComplete( QString parserId,
                      EveApiDataWalked processedDoc )
{
    QString requestId = this->_parserIdToRequestIdMap.take( parserId );
    this->_requestIdToParserIdMap.remove( requestId );
    this->_requestIdToParserMap.remove( requestId );
    QString req = this->_requestIdToRequestMap.take( requestId );
    // emit ...
    if (req == this->walletJournalRequestID())
    {
        emit journalWalkerRequestComplete( requestId, processedDoc );
    }
    else if (req == this->walletTransactionsRequestID())
    {
    }
}
#endif
