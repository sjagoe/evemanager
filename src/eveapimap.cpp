#include "eveapimap.hh"

#include "eveapisovereignty.hh"

/*!
create the child classes that provide API functionality
*/
EveApiMap::EveApiMap( QString& host, QString& dataPath, int& xmlIndent,
    QString& scope, QObject* parent )
        : EveApiScope ( host, dataPath, xmlIndent, scope, parent )
{
    // Sovereignty request
    QString requestID = this->sovereigntyRequestID();
    EveApiRequest* newRequest = new EveApiSovereignty(requestID,
        this->dataPath(), this->xmlIndent());
    this->addRequestType( requestID, newRequest );
}

/*!
access the RefTypes api function
*/
QString EveApiMap::sovereignty( QMap<QString, QString>& parameters )
{
    QString id = this->sovereigntyRequestID();
    return this->request( id, parameters );
}
