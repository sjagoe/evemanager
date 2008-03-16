#include "eveapieve.hh"

#include "eveapigeneralrequest.hh"

#include <QList>

EveApiEve::EveApiEve( QString& host, QString& dataPath, int& xmlIndent,
                      QString& scope, QObject* parent )
        : EveApiScope( host, dataPath, xmlIndent, scope, parent )
{
    this->createRequests();
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
Create request objects
*/
void EveApiEve::createRequest( QString& requestId,
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
void EveApiEve::createRequests()
{
    QStringList requiredParams;
    QStringList optionalParams;
    QStringList cacheID;

    // RefTypes request
    requiredParams.clear();
    requiredParams << "userID" << "apiKey";
    optionalParams.clear();
    cacheID.clear();
    QString requestID = this->refTypesRequestID();
    createRequest( requestID, requiredParams, optionalParams, cacheID );

    // SkillTree request
    requiredParams.clear();
    requiredParams << "userID" << "apiKey";
    optionalParams.clear();
    cacheID.clear();
    requestID = this->skillTreeRequestID();
    createRequest( requestID, requiredParams, optionalParams, cacheID );

    // AllianceList request
    requiredParams.clear();
    requiredParams << "userID" << "apiKey";
    optionalParams.clear();
    cacheID.clear();
    requestID = this->allianceListRequestID();
    createRequest( requestID, requiredParams, optionalParams, cacheID );

    // ErrorList request
    requiredParams.clear();
    requiredParams << "userID" << "apiKey";
    optionalParams.clear();
    cacheID.clear();
    requestID = this->errorListRequestID();
    createRequest( requestID, requiredParams, optionalParams, cacheID );
}
