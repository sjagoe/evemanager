#include "eveapicorporation.hh"

#include "eveapicharacterrequest.hh"

#include <QList>

/*!
create the child classes that provide API functionality
*/
EveApiCorporation::EveApiCorporation( QString& host, QString& dataPath, int& xmlIndent,
                                      QString& scope, QObject* parent )
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
}
