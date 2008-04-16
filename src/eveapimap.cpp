#include "eveapimap.hh"

#include "eveapigeneralrequest.hh"
#include <QList>

/*!
create the child classes that provide API functionality
*/
EveApiMap::EveApiMap( QString& host,
                      QString& dataPath,
                      int& xmlIndent,
                      QString& scope,
                      const int& proxyType,
                      const QString & proxyHost,
                      const quint16 & proxyPort,
                      const QString & proxyUser,
                      const QString & proxyPassword,
                      QObject* parent )
        : EveApiScope( host, dataPath, xmlIndent, scope, proxyType, proxyHost,
                        proxyPort, proxyUser, proxyPassword, parent )
{
    this->createRequests( proxyType, proxyHost, proxyPort, proxyUser,
                          proxyPassword );
}

/*!
access the Sovereignty api function
*/
QString EveApiMap::sovereignty( QMap<QString, QString>& parameters )
{
    QString id = this->sovereigntyRequestID();
    return this->request( id, parameters );
}

/*!
access the Jumps api function
*/
QString EveApiMap::jumps( QMap<QString, QString>& parameters )
{
    QString id = this->jumpsRequestID();
    return this->request( id, parameters );
}

/*!
access the Kills api function
*/
QString EveApiMap::kills( QMap<QString, QString>& parameters )
{
    QString id = this->killsRequestID();
    return this->request( id, parameters );
}

/*!
Create request objects
*/
void EveApiMap::createRequest( QString& requestId,
                               QStringList& requiredParams,
                               QStringList& optionalParams,
                               QStringList& cacheId,
                               const int& p_type,
                               const QString& host,
                               const quint16& port,
                               const QString & user,
                               const QString & password )
{
    EveApiRequest* newRequest = new EveApiGeneralRequest( requestId,
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
void EveApiMap::createRequests( const int& proxyType,
                                const QString & proxyHost,
                                const quint16 & proxyPort,
                                const QString & proxyUser,
                                const QString & proxyPassword )
{
    QStringList requiredParams;
    QStringList optionalParams;
    QStringList cacheID;

    // Sovereignty request
    requiredParams.clear();
    //requiredParams << "userID" << "apiKey";
    optionalParams.clear();
    cacheID.clear();
    QString requestID = this->sovereigntyRequestID();
    createRequest( requestID, requiredParams, optionalParams, cacheID,
                   proxyType, proxyHost, proxyPort, proxyUser, proxyPassword );

    // Jumps request
    requiredParams.clear();
    //requiredParams << "userID" << "apiKey";
    optionalParams.clear();
    cacheID.clear();
    requestID = this->jumpsRequestID();
    createRequest( requestID, requiredParams, optionalParams, cacheID,
                   proxyType, proxyHost, proxyPort, proxyUser, proxyPassword );

    // Kills request
    requiredParams.clear();
    //requiredParams << "userID" << "apiKey";
    optionalParams.clear();
    cacheID.clear();
    requestID = this->killsRequestID();
    createRequest( requestID, requiredParams, optionalParams, cacheID,
                   proxyType, proxyHost, proxyPort, proxyUser, proxyPassword );
}
