#include "eveapicharacter.hh"

#include "eveapicharacterrequest.hh"

//#if !defined(EVEAPI_NO_PARSING)
//#include "eveapiparser.hh"
//#endif

#include <QList>

/*!
create the child classes that provide API functionality
*/
EveApiCharacter::EveApiCharacter( QString& host, QString& dataPath, int& xmlIndent,
                                  QString& scope, QObject* parent )
        : EveApiScope( host, dataPath, xmlIndent, scope, parent )
{
//#if !defined(EVEAPI_NO_PARSING)
//    this->createParsers();
//#endif
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

