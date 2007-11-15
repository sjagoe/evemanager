#include "eveapimap.hh"

#include "eveapigeneralrequest.hh"

/*!
create the child classes that provide API functionality
*/
EveApiMap::EveApiMap( QString& host, QString& dataPath, int& xmlIndent,
    QString& scope, QObject* parent )
        : EveApiScope ( host, dataPath, xmlIndent, scope, parent )
{
    // Sovereignty request
    QString requestID = this->sovereigntyRequestID();
    EveApiRequest* newRequest = new EveApiGeneralRequest(requestID,
        this->dataPath(), this->xmlIndent());
    this->addRequestType( requestID, newRequest );
}

/*!
access the Sovereignty api function
*/
QString EveApiMap::sovereignty( QMap<QString, QString>& parameters )
{
    QString id = this->sovereigntyRequestID();
    return this->request( id, parameters );
}
