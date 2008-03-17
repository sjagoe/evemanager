#include "eveapicommon.hh"

#include "eveapicharacterrequest.hh"

/*!
create the child classes that provide API functionality
*/
EveApiCommon::EveApiCommon( QString& host, QString& dataPath, int& xmlIndent,
                                  QString& scope, QObject* parent )
        : EveApiScope( host, dataPath, xmlIndent, scope, parent )
{
    this->createCommonRequests();
}

/*!
access the WalletJournal api function
*/
QString EveApiCommon::walletJournal( QMap<QString, QString>& parameters )
{
    QString id = this->walletJournalRequestID();
    return this->request( id, parameters );
}

/*!
access the WalletTransactions api function
*/
QString EveApiCommon::walletTransactions( QMap<QString, QString>& parameters )
{
    QString id = this->walletTransactionsRequestID();
    return this->request( id, parameters );
}

/*!
access the AccountBalance api function
*/
QString EveApiCommon::accountBalance( QMap<QString, QString>& parameters )
{
    QString id = this->accountBalanceRequestID();
    return this->request( id, parameters );
}

/*!
access the IndustryJobs api function
*/
QString EveApiCommon::industryJobs( QMap<QString, QString>& parameters )
{
    QString id = this->industryJobsRequestID();
    return this->request( id, parameters );
}

/*!
access the AssetList api function
*/
QString EveApiCommon::assetList( QMap<QString, QString>& parameters )
{
    QString id = this->assetListRequestID();
    return this->request( id, parameters );
}

/*!
access the KillLog api function
*/
QString EveApiCommon::killLog( QMap<QString, QString>& parameters )
{
    QString id = this->killLogRequestID();
    return this->request( id, parameters );
}

/*!
access the MarketOrders api function
*/
QString EveApiCommon::marketOrders( QMap<QString, QString>& parameters )
{
    QString id = this->marketOrdersRequestID();
    return this->request( id, parameters );
}

/*!
Create request objects
*/
void EveApiCommon::createRequest( QString& requestId,
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

void EveApiCommon::createCommonRequests()
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

    // IndustryJobs request
    requiredParams.clear();
    requiredParams << "userID" << "characterID" << "apiKey";
    optionalParams.clear();
    cacheID.clear();
    requestID = this->industryJobsRequestID();
    createRequest( requestID, requiredParams, optionalParams, cacheID );

    // AssetList request
    requiredParams.clear();
    requiredParams << "userID" << "characterID" << "apiKey";
    optionalParams.clear();
    cacheID.clear();
    requestID = this->assetListRequestID();
    createRequest( requestID, requiredParams, optionalParams, cacheID );

    // KillLog request
    requiredParams.clear();
    requiredParams << "userID" << "characterID" << "apiKey";
    optionalParams.clear();
    optionalParams << "beforeKillID";
    cacheID.clear();
    cacheID << "beforeKillID";
    requestID = this->killLogRequestID();
    createRequest( requestID, requiredParams, optionalParams, cacheID );

    // MarketOrders request
    requiredParams.clear();
    requiredParams << "userID" << "characterID" << "apiKey";
    optionalParams.clear();
    cacheID.clear();
    requestID = this->killLogRequestID();
    createRequest( requestID, requiredParams, optionalParams, cacheID );
}
