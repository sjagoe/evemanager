#include "eveapicorporation.hh"

#include "eveapicharacterrequest.hh"

#include <QList>

/*!
create the child classes that provide API functionality
*/
EveApiCorporation::EveApiCorporation( QString& host, QString& dataPath, int& xmlIndent,
    QString& scope, QObject* parent )
        : EveApiScope ( host, dataPath, xmlIndent, scope, parent )
{
    QList<QString> requiredParams;
    QList<QString> optionalParams;

    // AccountBalance request
    requiredParams.clear();
    requiredParams.append( "userID" );
    requiredParams.append( "characterID" );
    requiredParams.append( "apiKey" );
    optionalParams.clear();
    QString requestID = this->accountBalanceRequestID();
    EveApiRequest* newRequest = new EveApiCharacterRequest(requestID,
        this->dataPath(),
        this->xmlIndent(),
            requiredParams,
            optionalParams);
    this->addRequestType( requestID, newRequest );

    // MemberTracking request
    requiredParams.clear();
    requiredParams.append( "userID" );
    requiredParams.append( "characterID" );
    requiredParams.append( "apiKey" );
    optionalParams.clear();
    requestID = this->memberTrackingRequestID();
    newRequest = new EveApiCharacterRequest(requestID,
        this->dataPath(),
        this->xmlIndent(),
            requiredParams,
            optionalParams);
    this->addRequestType( requestID, newRequest );
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
