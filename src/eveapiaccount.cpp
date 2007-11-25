#include "eveapiaccount.hh"

#include "eveapiaccountrequest.hh"

/*!
create the child classes that provide API functionality
*/
EveApiAccount::EveApiAccount( QString& host, QString& dataPath, int& xmlIndent,
    QString& scope, QObject* parent ) :
        EveApiScope( host, dataPath, xmlIndent, scope, parent )
{
    this->createRequests();
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
                                     QStringList& cacheId )
{
    EveApiRequest* newRequest = new EveApiAccountRequest( requestId,
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
void EveApiAccount::createRequests()
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
    createRequest( requestID, requiredParams, optionalParams, cacheID );
}
