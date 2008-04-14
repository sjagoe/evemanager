#include "eveapieve.hh"

#include "eveapigeneralrequest.hh"

#include <QList>

EveApiEve::EveApiEve( QString& host,
                      QString& dataPath,
                      int& xmlIndent,
                      QString& scope,
                      const int& proxyType,
                      const QString & proxyHost,
                      const quint16 & proxyPort,
                      const QString & proxyUser,
                      const QString & proxyPassword,
                      QObject* parent )
        : EveApiScope( host, dataPath, xmlIndent, scope, parent )
{
    this->createRequests( proxyType, proxyHost, proxyPort, proxyUser,
                          proxyPassword );
}

/*!
access the RefTypes api function
*/
QString EveApiEve::refTypes( QMap<QString, QString>& parameters )
{
    QString id = this->refTypesRequestID();
    return this->request( id, parameters );
}

/*!
access the SkillTree api function
*/
QString EveApiEve::skillTree( QMap<QString, QString>& parameters )
{
    QString id = this->skillTreeRequestID();
    return this->request( id, parameters );
}

/*!
access the AllianceList api function
*/
QString EveApiEve::allianceList( QMap<QString, QString>& parameters )
{
    QString id = this->allianceListRequestID();
    return this->request( id, parameters );
}

/*!
access the ErrorList api function
*/
QString EveApiEve::errorList( QMap<QString, QString>& parameters )
{
    QString id = this->errorListRequestID();
    return this->request( id, parameters );
}

/*!
access the CharacterID api function
*/
QString EveApiEve::characterID( QMap<QString, QString>& parameters )
{
    QString id = this->characterIDRequestID();
    return this->request( id, parameters );
}

/*!
access the ConquerableStationsList api function
*/
QString EveApiEve::conquerableStationsList( QMap<QString, QString>& parameters )
{
    QString id = this->conquerableStationsListRequestID();
    return this->request( id, parameters );
}

/*!
Create request objects
*/
void EveApiEve::createRequest( QString& requestId,
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
void EveApiEve::createRequests( const int& proxyType,
                                const QString & proxyHost,
                                const quint16 & proxyPort,
                                const QString & proxyUser,
                                const QString & proxyPassword )
{
    QStringList requiredParams;
    QStringList optionalParams;
    QStringList cacheID;

    // RefTypes request
    requiredParams.clear();
    //requiredParams << "userID" << "apiKey";
    optionalParams.clear();
    cacheID.clear();
    QString requestID = this->refTypesRequestID();
    createRequest( requestID, requiredParams, optionalParams, cacheID,
                   proxyType, proxyHost, proxyPort, proxyUser, proxyPassword );

    // SkillTree request
    requiredParams.clear();
    //requiredParams << "userID" << "apiKey";
    optionalParams.clear();
    cacheID.clear();
    requestID = this->skillTreeRequestID();
    createRequest( requestID, requiredParams, optionalParams, cacheID,
                   proxyType, proxyHost, proxyPort, proxyUser, proxyPassword );

    // AllianceList request
    requiredParams.clear();
    //requiredParams << "userID" << "apiKey";
    optionalParams.clear();
    cacheID.clear();
    requestID = this->allianceListRequestID();
    createRequest( requestID, requiredParams, optionalParams, cacheID,
                   proxyType, proxyHost, proxyPort, proxyUser, proxyPassword );

    // ErrorList request
    requiredParams.clear();
    //requiredParams << "userID" << "apiKey";
    optionalParams.clear();
    cacheID.clear();
    requestID = this->errorListRequestID();
    createRequest( requestID, requiredParams, optionalParams, cacheID,
                   proxyType, proxyHost, proxyPort, proxyUser, proxyPassword );

    // CharacterID request
    requiredParams.clear();
    //requiredParams << "userID" << "apiKey";
    optionalParams.clear();
    cacheID.clear();
    requestID = this->characterIDRequestID();
    createRequest( requestID, requiredParams, optionalParams, cacheID,
                   proxyType, proxyHost, proxyPort, proxyUser, proxyPassword );

    // ConquerableStationsList request
    requiredParams.clear();
    //requiredParams << "userID" << "apiKey";
    optionalParams.clear();
    cacheID.clear();
    requestID = this->conquerableStationsListRequestID();
    createRequest( requestID, requiredParams, optionalParams, cacheID,
                   proxyType, proxyHost, proxyPort, proxyUser, proxyPassword );
}
