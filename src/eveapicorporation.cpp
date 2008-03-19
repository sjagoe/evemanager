#include "eveapicorporation.hh"

#include "eveapicharacterrequest.hh"

#include <QList>

/*!
create the child classes that provide API functionality
*/
EveApiCorporation::EveApiCorporation( QString& host,
                                      QString& dataPath,
                                      int& xmlIndent,
                                      QString& scope,
                                      QObject* parent )
        : EveApiCommon( host, dataPath, xmlIndent, scope, parent )
{
    this->createRequests();
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
access the CorporationSheet api function
*/
QString EveApiCorporation::corporationSheet(
    QMap<QString, QString>& parameters )
{
    QString id = this->corporationSheetRequestID();
    return this->request( id, parameters );
}

/*!
access the StarbaseList api function
*/
QString EveApiCorporation::starbaseList( QMap<QString, QString>& parameters )
{
    QString id = this->starbaseListRequestID();
    return this->request( id, parameters );
}

/*!
access the StarbaseDetail api function
*/
QString EveApiCorporation::starbaseDetail( QMap<QString, QString>& parameters )
{
    QString id = this->starbaseDetailRequestID();
    return this->request( id, parameters );
}

/*!
create all requests (delegated from the constructor)
*/
void EveApiCorporation::createRequests()
{
    QStringList requiredParams;
    QStringList optionalParams;
    QStringList cacheID;

    // MemberTracking request
    requiredParams.clear();
    requiredParams << "userID" << "characterID" << "apiKey";
    optionalParams.clear();
    cacheID.clear();
    QString requestID = this->memberTrackingRequestID();
    createRequest( requestID, requiredParams, optionalParams, cacheID );

    // CorporationSheet request
    requiredParams.clear();
    requiredParams << "userID" << "characterID" << "apiKey";
    optionalParams.clear();
    cacheID.clear();
    requestID = this->corporationSheetRequestID();
    createRequest( requestID, requiredParams, optionalParams, cacheID );

    // CorporationSheet request
    requiredParams.clear();
    requiredParams << "userID" << "characterID" << "apiKey" << "version";
    optionalParams.clear();
    cacheID.clear();
    requestID = this->starbaseListRequestID();
    createRequest( requestID, requiredParams, optionalParams, cacheID );

    // CorporationSheet request
    requiredParams.clear();
    requiredParams << "userID" << "characterID" << "apiKey" << "version";
    optionalParams.clear();
    cacheID.clear();
    requestID = this->starbaseDetailRequestID();
    createRequest( requestID, requiredParams, optionalParams, cacheID );
}
