#include "eveapirequest.hh"

#include <QCoreApplication>

#include <QHttp>
#include <QBuffer>

#include <QFile>
#include <QDir>
#include <QTextStream>

EveApiRequest::EveApiRequest( QString& requestType, QString& dataPath, int& xmlIndent, QObject* parent )
    : QObject ( parent )
{
    this->_http = new QHttp;
    this->_requestType = requestType;
    this->_dataPath = dataPath;
    this->_xmlIndent = xmlIndent;
    this->_currentRequest = 0;
}

/*!
Add a request to be handled.

\return unique request identifier (used to id a completed request)
*/
QString EveApiRequest::addRequest( QString& host, QString& scope,
    QMap<QString, QString>& parameters )
{
    int id = 0;

    QString idStr = QString();

    QString pathText = this->path( scope );

    QUrl url( pathText );
    if (this->validateParamaters( parameters, url ))
    {
        QHttpRequestHeader head("POST", pathText);
        head.setValue("Host", host);
        head.setValue("Content-type", "application/x-www-form-urlencoded");

        QBuffer* data = new QBuffer;
        QBuffer* to = new QBuffer;

        data->setData(url.encodedQuery());

        this->_http->setHost( host );
        id = this->_http->request(head, data, to);

        this->_requestBuffers.insert( id, qMakePair( data, to ) );

        this->_requests.insert( id, qMakePair( scope, this->requestType() ) );

        idStr = makeID(scope, id);

        this->_id.insert(id, idStr);

        this->_characterID.insert( id, qMakePair( parameters.value( "userID" ), parameters.value( "charID" )) );
    }
    return idStr;
}

/*!
return the server path (URI) to access the requested information
*/
QString EveApiRequest::path( const QString& scope )
{
    QString pathStr = "/";
    pathStr = pathStr.append(scope);
    pathStr = pathStr.append("/");
    pathStr = pathStr.append(this->requestType());
    return pathStr;
}

const QString& EveApiRequest::requestType() const
{
    return this->_requestType;
}

/*!
make a unique string ID
*/
QString EveApiRequest::makeID( const QString& scope, int& id )
{
    QString idStr = this->path( scope );
    idStr = idStr.append(QString("-%1").arg(id));
    return idStr;
}

/*!
signal that a request has begun
*/
void EveApiRequest::requestStarted( int id )
{
    this->_currentRequest = id;
}

/*!
signal that a request has finished so that the result can be delivered
*/
void EveApiRequest::requestFinished( int id, bool error )
{
    this->_currentRequest = 0;

    QPair<QBuffer*, QBuffer*> buffers = this->_requestBuffers.take(id);
    QPair<QString, QString> request = this->_requests.take(id);
    QString idStr = this->_id.take(id);
    QString response = this->_response.take(id);
    QPair<QString, QString> characterID = this->_characterID.take(id);

    if (error)
    {
        QString err = this->_http->errorString();
        emit requestFailed( idStr, err, response );
    }
    else
    {
        QDir cwd(QCoreApplication::applicationDirPath());
        if (!cwd.exists( this->_dataPath ))
        {
            cwd.mkdir( this->_dataPath );
        }
        cwd.cd( this->_dataPath );

        QStringList dirs = this->cachePath( characterID );
        QString dir;
        foreach( dir, dirs )
        {
            if (!cwd.exists( dir ))
            {
                cwd.mkdir( dir );
            }
            cwd.cd( dir );
        }

        QString thisCachePath = cwd.path();

        thisCachePath = thisCachePath.append("/");
        thisCachePath = thisCachePath.append(this->requestType());

        QDomDocument xmlData;
        xmlData.setContent( buffers.second );
        QFile saveFile( thisCachePath );

        if (saveFile.open( QIODevice::WriteOnly | QIODevice::Truncate ))
        {
            QTextStream save( &saveFile );
            xmlData.save( save, this->_xmlIndent );
            saveFile.close();
        }
        emit requestComplete( idStr, xmlData, response );
    }
    delete buffers.first;
    buffers.first = 0;
    delete buffers.second;
    buffers.second = 0;
}

/*!
An http response is received
*/
void EveApiRequest::responseHeaderReceived( QHttpResponseHeader head )
{
    QString response = QString("%1 - ").arg(head.statusCode());
    response = response.append(head.reasonPhrase());

    this->_response.insert(this->_currentRequest, response);
}
