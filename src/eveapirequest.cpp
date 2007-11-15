#include "eveapirequest.hh"

//#include <iostream>

#include <QCoreApplication>

#include <QHttp>
#include <QBuffer>

#include <QFile>
#include <QDir>
#include <QTextStream>

EveApiRequest::EveApiRequest( const QString& requestType,
    const QString& dataPath, const int& xmlIndent,
    const QList<QString>& requiredParams, const QList<QString>& optionalParams,
    QObject* parent )
        : QObject ( parent )
{
    this->_http = new QHttp;
    this->_requestType = requestType;
    this->_dataPath = dataPath;
    this->_xmlIndent = xmlIndent;
    this->_requiredParamaters = requiredParams;
    this->_optionalParameters = optionalParams;
    this->_currentRequest = 0;

    connect( this->_http, SIGNAL(requestStarted( int )),
        this, SLOT( requestStarted( int ) ));

    connect( this->_http, SIGNAL(requestFinished( int, bool )),
        this, SLOT( requestFinished( int, bool ) ) );

    connect( this->_http, SIGNAL(responseHeaderReceived( QHttpResponseHeader ) ),
        this, SLOT( responseHeaderReceived( QHttpResponseHeader ) ) );
}

/*!
Add a request to be handled.

\return unique request identifier (used to id a completed request)
*/
QString EveApiRequest::addRequest( const QString& host, const QString& scope,
    QMap<QString, QString>& parameters )
{
//    std::cout << "EveApiRequest::addRequest()" << std::endl;

    QString idStr = QString();

    QStringList cacheDirs = cachePath( scope, parameters );

    QString cachePathStr(QCoreApplication::applicationDirPath());
    cachePathStr = cachePathStr.append( "/" );
    cachePathStr = cachePathStr.append( this->_dataPath );
    QString dir;
    foreach( dir, cacheDirs )
    {
        cachePathStr = cachePathStr.append( "/" );
        cachePathStr = cachePathStr.append( dir );
    }
    cachePathStr = cachePathStr.append( "/" );
    cachePathStr = cachePathStr.append( this->requestType() );

//    std::cout << cachePathStr.toStdString() << std::endl;

    QDomDocument cacheDom;

    QFile loadFile( cachePathStr );
    if (loadFile.open( QIODevice::ReadOnly ))
    {
//        std::cout << "check file" << std::endl;
        if ( cacheDom.setContent( &loadFile ) )
        {
//            std::cout << "load xml" << std::endl;
            loadFile.close();
            // file loaded
            QDateTime cacheTime = this->getCacheTime( cacheDom );
            QDateTime now = QDateTime::currentDateTime();
            QDateTime nowUTC = now.toUTC();
            // over by 30 secs, prevent accidental fetch if the cache has not
            // expired (due to differences in clocks)
            if (nowUTC.secsTo(cacheTime) <= -30)
            {
//                std::cout << "cache expired, fetch new" << std::endl;
                // cache invalid, fetch new
                idStr = this->fetchFromApi( host, scope, parameters );
            }
            else
            {
//                std::cout << "cache valid" << std::endl;
                // cache valid, return it
                idStr = this->path( scope );
//                idStr = "/";
//                idStr = idStr.append(scope);
//                idStr = idStr.append("/");
//                idStr = idStr.append(requestType());
                idStr = idStr.append("-");
                idStr = idStr.append(parameters.value("userID"));
                idStr = idStr.append("-");
                idStr = idStr.append(parameters.value("characterID"));
                idStr = idStr.append("-");
                idStr = idStr.append(parameters.value("apiKey"));

                emit requestComplete( idStr, cacheDom, QString("FROM CACHE") );
            }
        }
        else
        {
//            std::cout << "unable to load file, fetch new" << std::endl;
            loadFile.close();
            // error (fetch new one?)
            idStr = this->fetchFromApi( host, scope, parameters );
        }
    }
    else
    {
//        std::cout << "no cache, fetch new" << std::endl;
        idStr = this->fetchFromApi( host, scope, parameters );
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
    pathStr = pathStr.append( QString( this->fileExtension() ) );
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
Check the paramaters
*/
bool EveApiRequest::validateParamaters( const QMap<QString, QString>& parameters, QUrl& url )
{
    QString paramID;
    // check all the required params
    foreach( paramID, this->_requiredParamaters )
    {
        QString param = parameters.value( paramID );
        if (param.isNull());
            return false;
        url.addQueryItem(paramID, param);
    }
    // check optional parameters
    foreach( paramID, this->_optionalParameters )
    {
        QString param = parameters.value( paramID );
        if (!param.isNull());
            url.addQueryItem(paramID, param);
    }
    return true;
}

/*!
Fetch from API
*/
QString EveApiRequest::fetchFromApi( const QString& host, const QString& scope,
    const QMap<QString, QString>& parameters )
{
    int id = 0;

    QString idStr = QString();

    QString serverPath = this->path( scope );

    QUrl url( serverPath );
    if (this->validateParamaters( parameters, url ))
    {
        QHttpRequestHeader head("POST", serverPath);
        head.setValue("Host", host);
        head.setValue("Content-type", "application/x-www-form-urlencoded");

        QBuffer* data = new QBuffer;

        data->setData(url.encodedQuery());

        this->_http->setHost( host );
        id = this->_http->request(head, data);

        this->_requestBuffers.insert( id, data );

        this->_requests.insert( id, qMakePair( scope, this->requestType() ) );

        idStr = makeID(scope, id);

        this->_id.insert(id, idStr);

        this->_paramaters.insert( id, parameters );
    }
    return idStr;
}

/*!
Get the time that the cache expires from a QDomDocument
*/
QDateTime EveApiRequest::getCacheTime( const QDomDocument& xmlDocument )
{
    QString currentTimeString;
    QString cachedUntilString;
    QDateTime cachedUntil;
    QDomElement root = xmlDocument.documentElement();
    if (root.tagName() != "eveapi")
    {
        return QDateTime();
    }
//    if (root.attribute( "version" ) != QString("1"))
//    {
//        return QDateTime();
//    }

    QDomNode firstLevel = root.firstChild();
    while ( !firstLevel.isNull() )
    {
        if ( firstLevel.toElement().tagName() == QString("cachedUntil") )
        {
            cachedUntilString = firstLevel.toElement().text();
            cachedUntil = this->eveApiTimeToQDateTime( cachedUntilString );
        }
        firstLevel = firstLevel.nextSibling();
    }
    return cachedUntil;
}

/*!
convert a time specified in the API XML output to a QDateTime
*/
QDateTime EveApiRequest::eveApiTimeToQDateTime( QString timeString )
{
    QStringList dateAndTime = timeString.split(" ");
    QStringList dateStrings = dateAndTime.at(0).split("-");
    QStringList timeStrings = dateAndTime.at(1).split(":");

    int year = dateStrings.at(0).toInt();
    int month = dateStrings.at(1).toInt();
    int day = dateStrings.at(2).toInt();

    int hours = timeStrings.at(0).toInt();
    int minutes = timeStrings.at(1).toInt();
    int seconds = timeStrings.at(2).toInt();

    QDate date(year, month, day);
    QTime time(hours, minutes, seconds);

    QDateTime dateTime(date, time, Qt::UTC);

    return dateTime;
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
//    std::cout << "EveApiRequest::requestFinished()" << std::endl;
    this->_currentRequest = 0;

    QBuffer* buffer = this->_requestBuffers.take(id);
    QPair<QString, QString> request = this->_requests.take(id);
    QString scope = request.first;
    QString idStr = this->_id.take(id);
    QString response = this->_response.take(id);
    QMap<QString, QString> parameters = this->_paramaters.take(id);

    QByteArray data = this->_http->readAll();

    if (error)
    {
        QString err = this->_http->errorString();
        emit requestFailed( idStr, err, response );
    }
    else
    {
        if (!scope.isEmpty())
        {
            QDir cwd(QCoreApplication::applicationDirPath());
            if (!cwd.exists( this->_dataPath ))
            {
                cwd.mkdir( this->_dataPath );
            }
            cwd.cd( this->_dataPath );

            QStringList dirs = this->cachePath( scope, parameters );
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
            xmlData.setContent( data );

//            std::cout << data.data() << std::endl;

            QFile saveFile( thisCachePath );

            if (saveFile.open( QIODevice::ReadWrite | QIODevice::Truncate ))
            {
                QTextStream save( &saveFile );
                xmlData.save( save, this->_xmlIndent );
                saveFile.close();
            }
            emit requestComplete( idStr, xmlData, response );
        }
    }
    delete buffer;
    buffer = 0;
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
