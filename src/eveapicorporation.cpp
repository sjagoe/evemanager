#include "eveapicorporation.hh"

#include "eveapicharacterrequest.hh"

#include <QList>

/*!
create the child classes that provide API functionality
*/
EveApiCorporation::EveApiCorporation( QString& host, QString& dataPath, int& xmlIndent,
                                      QString& scope, QObject* parent )
        : EveApiScope( host, dataPath, xmlIndent, scope, parent )
{
    QList<QString> requiredParams;
    QList<QString> optionalParams;
    QList<QString> cacheID;

    // AccountBalance request
    requiredParams.clear();
    requiredParams.append( "userID" );
    requiredParams.append( "characterID" );
    requiredParams.append( "apiKey" );
    optionalParams.clear();
    cacheID.clear();
    QString requestID = this->accountBalanceRequestID();
    EveApiRequest* newRequest = new EveApiCharacterRequest( requestID,
            this->dataPath(),
            this->xmlIndent(),
            requiredParams,
            optionalParams,
            cacheID );
    this->addRequestType( requestID, newRequest );

    // MemberTracking request
    requiredParams.clear();
    requiredParams.append( "userID" );
    requiredParams.append( "characterID" );
    requiredParams.append( "apiKey" );
    optionalParams.clear();
    cacheID.clear();
    requestID = this->memberTrackingRequestID();
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
    optionalParams.append( "accountKey" );
    optionalParams.append( "beforeRefID" );
    cacheID.clear();
    cacheID.append( "accountKey" );
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
    optionalParams.append( "accountKey" );
    optionalParams.append( "beforeTransID" );
    cacheID.clear();
    cacheID.append( "accountKey" );
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
access the WalletJournal api function
*/
QString EveApiCorporation::walletJournal( QMap<QString, QString>& parameters )
{
    QString id = this->walletJournalRequestID();
    return this->request( id, parameters );
}

/*!
access the WalletTransactions api function
*/
QString EveApiCorporation::walletTransactions( QMap<QString, QString>& parameters )
{
    QString id = this->walletTransactionsRequestID();
    return this->request( id, parameters );
}

/*!
access the AccountBalance api function
*/
QString EveApiCorporation::accountBalance( QMap<QString, QString>& parameters )
{
    QString id = this->accountBalanceRequestID();
    return this->request( id, parameters );
}

/*!
access the MemberTracking api function
*/
QString EveApiCorporation::memberTracking( QMap<QString, QString>& parameters )
{
    QString id = this->memberTrackingRequestID();
    return this->request( id, parameters );
}
