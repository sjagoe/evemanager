#include "eveapicharacter.hh"

#include "eveapicharacterrequest.hh"

#include <QList>

/*!
create the child classes that provide API functionality
*/
EveApiCharacter::EveApiCharacter( QString& host, QString& dataPath, int& xmlIndent,
                                  QString& scope, QObject* parent )
        : EveApiScope( host, dataPath, xmlIndent, scope, parent )
{
    QList<QString> requiredParams;
    QList<QString> optionalParams;
    QList<QString> cacheID;

    // CharacterSheet request
    requiredParams.clear();
    requiredParams.append( "userID" );
    requiredParams.append( "characterID" );
    requiredParams.append( "apiKey" );
    optionalParams.clear();
    cacheID.clear();
    QString requestID = this->characterSheetRequestID();
    EveApiRequest* newRequest = new EveApiCharacterRequest( requestID,
            this->dataPath(),
            this->xmlIndent(),
            requiredParams,
            optionalParams,
            cacheID );
    this->addRequestType( requestID, newRequest );

    // SkillInTraining request
    requiredParams.clear();
    requiredParams.append( "userID" );
    requiredParams.append( "characterID" );
    requiredParams.append( "apiKey" );
    optionalParams.clear();
    cacheID.clear();
    requestID = this->skillInTrainingRequestID();
    newRequest = new EveApiCharacterRequest( requestID,
            this->dataPath(),
            this->xmlIndent(),
            requiredParams,
            optionalParams,
            cacheID );
    this->addRequestType( requestID, newRequest );

    // AccountBalance request
    requiredParams.clear();
    requiredParams.append( "userID" );
    requiredParams.append( "characterID" );
    requiredParams.append( "apiKey" );
    optionalParams.clear();
    cacheID.clear();
    requestID = this->accountBalanceRequestID();
    newRequest = new EveApiCharacterRequest( requestID,
            this->dataPath(),
            this->xmlIndent(),
            requiredParams,
            optionalParams,
            cacheID );
    this->addRequestType( requestID, newRequest );

    // WalletJournal request
    requiredParams.clear();
    requiredParams.append( "userID" );
    requiredParams.append( "characterID" );
    requiredParams.append( "apiKey" );
    optionalParams.clear();
    //optionalParams.append( "accountKey" );
    optionalParams.append( "beforeRefID" );
    cacheID.clear();
    cacheID.append( "beforeRefID" );
    requestID = this->walletJournalRequestID();
    newRequest = new EveApiCharacterRequest( requestID,
            this->dataPath(),
            this->xmlIndent(),
            requiredParams,
            optionalParams,
            cacheID );
    this->addRequestType( requestID, newRequest );

    // WalletTransactions request
    requiredParams.clear();
    requiredParams.append( "userID" );
    requiredParams.append( "characterID" );
    requiredParams.append( "apiKey" );
    optionalParams.clear();
    //optionalParams.append( "accountKey" );
    optionalParams.append( "beforeTransID" );
    cacheID.clear();
    cacheID.append( "beforeTransID" );
    requestID = this->walletTransactionsRequestID();
    newRequest = new EveApiCharacterRequest( requestID,
            this->dataPath(),
            this->xmlIndent(),
            requiredParams,
            optionalParams,
            cacheID );
    this->addRequestType( requestID, newRequest );
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
