#include "eveapimap.hh"

#include "eveapigeneralrequest.hh"
#include <QList>

/*!
create the child classes that provide API functionality
*/
EveApiMap::EveApiMap( QString& host, QString& dataPath, int& xmlIndent,
                      QString& scope, QObject* parent )
        : EveApiScope( host, dataPath, xmlIndent, scope, parent )
{
    this->createRequests();
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
Create request objects
*/
void EveApiMap::createRequest( QString& requestId,
                                     QStringList& requiredParams,
                                     QStringList& optionalParams,
                                     QStringList& cacheId )
{
    EveApiRequest* newRequest = new EveApiGeneralRequest( requestId,
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
void EveApiMap::createRequests()
{
    QStringList requiredParams;
    QStringList optionalParams;
    QStringList cacheID;

    // Sovereignty request
    requiredParams.clear();
    requiredParams << "userID" << "apiKey";
    optionalParams.clear();
    cacheID.clear();
    QString requestID = this->sovereigntyRequestID();
    createRequest( requestID, requiredParams, optionalParams, cacheID );
}
