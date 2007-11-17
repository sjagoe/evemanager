#include "eveapiscope.hh"

#include "eveapirequest.hh"

#include <Qt>
#include <QMetaType>

/*!
create the child classes that provide API functionality
*/
EveApiScope::EveApiScope( QString& host, QString& dataPath, int& xmlIndent,
    QString& scope, QObject* parent )
        : QObject( parent )
{
    this->_hostName = host;
    this->_dataPath = dataPath;
    this->_xmlIndent = xmlIndent;
    this->_scope = scope;

    qRegisterMetaType<QDomDocument>("QDomDocument");
    qRegisterMetaType<QDateTime>("QDateTime");
}


/*!
Get the host of the API server
*/
const QString& EveApiScope::hostName()
{
    return this->_hostName;
}

/*!
Get the local data subdir
*/
const QString& EveApiScope::dataPath()
{
    return this->_dataPath;
}

/*!
get the XML Indent amount
*/
const int& EveApiScope::xmlIndent()
{
    return this->_xmlIndent;
}

/*!
get the current scope
*/
const QString& EveApiScope::scope()
{
    return this->_scope;
}

/*!
Add a "Request Type" to the list
*/
void EveApiScope::addRequestType( QString& id, EveApiRequest* request )
{
    connect( request,
        SIGNAL(requestComplete( QString, QDomDocument, QString, QDateTime )),
        this, SIGNAL(requestComplete( QString, QDomDocument, QString, QDateTime )),
        Qt::QueuedConnection );
    connect( request,
        SIGNAL(requestFailed( QString, QString, QString )),
        this, SIGNAL(requestFailed( QString, QString, QString )),
        Qt::QueuedConnection );

    this->_apiRequests.insert( id, request );
}

/*!
Add a request of the specified type
*/
QString EveApiScope::request( QString& id, QMap<QString, QString>& parameters )
{
    this->_mutex.lock();
    QString host = this->hostName();
    QString scopeStr = this->scope();
    EveApiRequest* req = this->requestType( id );
    QString result;
    if (req)
    {
        result = req->addRequest( host, scopeStr, parameters );
    }
    this->_mutex.unlock();
    return result;
}

/*!
return a previously added request type
*/
EveApiRequest* EveApiScope::requestType( QString& id ) const
{
    return this->_apiRequests.value( id );
}
