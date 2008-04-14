#include "eveapiaccount.hh"

#include "eveapiaccountrequest.hh"

/*!
create the child classes that provide API functionality
*/
EveApiAccount::EveApiAccount( QString& host,
                              QString& dataPath,
                              int& xmlIndent,
                              QString& scope,
                              const int& proxyType,
                              const QString & proxyHost,
                              const quint16 & proxyPort,
                              const QString & proxyUser,
                              const QString & proxyPassword,
                              QObject* parent ) :
        EveApiScope( host, dataPath, xmlIndent, scope, parent )
{
    this->createRequests( proxyType, proxyHost, proxyPort, proxyUser,
                          proxyPassword );
}

/*!
access the Characters api function
*/
QString EveApiAccount::characters( QMap<QString, QString>& parameters )
{
    QString id = this->charactersRequestID();
    return this->request( id, parameters );
}

/*!
Create request objects
*/
void EveApiAccount::createRequest( QString& requestId,
                                   QStringList& requiredParams,
                                   QStringList& optionalParams,
                                   QStringList& cacheId,
                                   const int& p_type,
                                   const QString& host,
                                   const quint16& port,
                                   const QString & user,
                                   const QString & password )
{
    EveApiRequest* newRequest = new EveApiAccountRequest( requestId,
            this->dataPath(),
            this->xmlIndent(),
            requiredParams,
            optionalParams,
            cacheId,
            p_type,
            host,
            port,
            user,
            password );
    this->addRequestType( requestId, newRequest );
}

/*!
create all requests (delegated from the constructor)
*/
void EveApiAccount::createRequests( const int& proxyType,
                                    const QString & proxyHost,
                                    const quint16 & proxyPort,
                                    const QString & proxyUser,
                                    const QString & proxyPassword )
{
    QStringList requiredParams;
    QStringList optionalParams;
    QStringList cacheID;

    // Character request
    requiredParams.clear();
    requiredParams << "userID" << "apiKey";
    optionalParams.clear();
    cacheID.clear();
    QString requestID = this->charactersRequestID();
    createRequest( requestID, requiredParams, optionalParams, cacheID,
                   proxyType, proxyHost, proxyPort, proxyUser, proxyPassword );
}
