#include "eveapieve.hh"

#include "eveapigeneralrequest.hh"
//#include "eveapiskilltree.hh"

EveApiEve::EveApiEve( QString& host, QString& dataPath, int& xmlIndent,
    QString& scope, QObject* parent )
        : EveApiScope ( host, dataPath, xmlIndent, scope, parent )
{
    // RefTypes request
    QString requestID = this->refTypesRequestID();
    EveApiRequest* newRequest = new EveApiGeneralRequest(requestID, this->dataPath(),
        this->xmlIndent());
    this->addRequestType( requestID, newRequest );

    // SkillTree request
    requestID = this->skillTreeRequestID();
    newRequest = new EveApiGeneralRequest(requestID, this->dataPath(),
        this->xmlIndent());
    this->addRequestType( requestID, newRequest );
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

