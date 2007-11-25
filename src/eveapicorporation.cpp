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
    this->createRequests();
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

/*!
Create request objects
*/
void EveApiCorporation::createRequest( QString& requestId,
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
void EveApiCorporation::createRequests()
{
    QStringList requiredParams;
    QStringList optionalParams;
    QStringList cacheID;

    // AccountBalance request
    requiredParams.clear();
    requiredParams << "userID" << "characterID" << "apiKey";
    optionalParams.clear();
    cacheID.clear();
    QString requestID = this->accountBalanceRequestID();
    createRequest( requestID, requiredParams, optionalParams, cacheID );

    // MemberTracking request
    requiredParams.clear();
    requiredParams << "userID" << "characterID" << "apiKey";
    optionalParams.clear();
    cacheID.clear();
    requestID = this->memberTrackingRequestID();
    createRequest( requestID, requiredParams, optionalParams, cacheID );

    // WalletJournal request
    requiredParams.clear();
    requiredParams << "userID" << "characterID" << "apiKey";
    optionalParams.clear();
    optionalParams << "accountKey" << "beforeRefID";
    cacheID.clear();
    cacheID << "accountKey" << "beforeRefID";
    requestID = this->walletJournalRequestID();
    createRequest( requestID, requiredParams, optionalParams, cacheID );

    // WalletTransactions request
    requiredParams.clear();
    requiredParams << "userID" << "characterID" << "apiKey";
    optionalParams.clear();
    optionalParams << "accountKey" << "beforeTransID";
    cacheID.clear();
    cacheID << "accountKey" << "beforeTransID";
    requestID = this->walletTransactionsRequestID();
    createRequest( requestID, requiredParams, optionalParams, cacheID );
}
