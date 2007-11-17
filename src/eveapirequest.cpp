#include "eveapirequest.hh"

//#include <iostream>

#include <QCoreApplication>

#include <QHttp>
#include <QBuffer>

#include <QFile>
#include <QDir>
#include <QTextStream>

EveApiRequest::EveApiRequest( const QString& requestType,
                              const QString& dataPath,
                              const int& xmlIndent,
                              const QList<QString>& requiredParams,
                              const QList<QString>& optionalParams,
                              const QList<QString>& fileIDParam,
                              QObject* parent )
        : QObject( parent )
{
    this->_http = new QHttp;
    this->_requestType = requestType;
    this->_dataPath = dataPath;
    this->_xmlIndent = xmlIndent;
    this->_requiredParamaters = requiredParams;
    this->_optionalParameters = optionalParams;
    this->_fileIDParam = fileIDParam;
    this->_currentRequest = 0;

    connect( this->_http, SIGNAL( requestStarted( int ) ),
             this, SLOT( requestStarted( int ) ) );

    connect( this->_http, SIGNAL( requestFinished( int, bool ) ),
             this, SLOT( requestFinished( int, bool ) ) );

    connect( this->_http, SIGNAL( responseHeaderReceived( QHttpResponseHeader ) ),
             this, SLOT( responseHeaderReceived( QHttpResponseHeader ) ) );
}

/*!
Add a request to be handled.

\return unique request identifier (used to id a completed request)
*/
QString EveApiRequest::addRequest( const QString& host, const QString& scope,
                                   QMap<QString, QString>& parameters,
                                   bool internal )
{
    QString idStr = QString();

    QStringList cacheDirs = cachePath( scope, parameters );

    QString cachePathStr( QCoreApplication::applicationDirPath() );
    cachePathStr = cachePathStr.append( "/" );
    cachePathStr = cachePathStr.append( this->_dataPath );
    QString dir;
    foreach( dir, cacheDirs )
    {
        cachePathStr = cachePathStr.append( "/" );
        cachePathStr = cachePathStr.append( dir );
    }
    cachePathStr = cachePathStr.append( "/" );
    QString cacheID;
    foreach( cacheID, this->_fileIDParam )
    {
        cachePathStr = cachePathStr.append( parameters.value( cacheID ) );
    }
    cachePathStr = cachePathStr.append( this->requestType() );

    QDomDocument cacheDom;

    QFile loadFile( cachePathStr );
    if ( loadFile.open( QIODevice::ReadOnly ) )
    {
        if ( cacheDom.setContent( &loadFile ) )
        {
            loadFile.close();
            // file loaded
            QDateTime cacheTime = this->getCacheTime( cacheDom );
            QDateTime now = QDateTime::currentDateTime();
            QDateTime nowUTC = now.toUTC();
            // over by 60 secs, prevent accidental fetch if the cache has not
            // expired (due to differences in clocks)
            if ( nowUTC.secsTo( cacheTime ) <= -60 )
            {
                // cache invalid, fetch new
                this->cleanCache( scope, parameters );
                idStr = this->fetchFromApi( host, scope, parameters, internal );
            }
            else
            {
                int idi = 0;
                idStr = this->makeID( scope, idi, parameters );
                if ( internal )
                {
                    emit internalRequestComplete( idStr, cacheDom, QString( "FROM LOCAL CACHE" ), cacheTime );
                }
                else
                {
                    emit requestComplete( idStr, cacheDom, QString( "FROM LOCAL CACHE" ), cacheTime );
                }
            }
        }
        else
        {
            loadFile.close();
            this->cleanCache( scope, parameters );
            // error (fetch new one?)
            idStr = this->fetchFromApi( host, scope, parameters, internal );
        }
    }
    else
    {
        idStr = this->fetchFromApi( host, scope, parameters, internal );
    }

    return idStr;
}

// /*!
//Add an internal request to be handled.
//
//\return unique request identifier (used to id a completed request)
//*/
//QString EveApiRequest::addInternalRequest( const QString& host,
//        const QString& scope,
//        QMap<QString, QString>& parameters )
//{
//    this->addRequest( host, scope, parameters, true );
//}

/*!
return the server path (URI) to access the requested information
*/
QString EveApiRequest::path( const QString& scope )
{
    QString pathStr = "/";
    pathStr = pathStr.append( scope );
    pathStr = pathStr.append( "/" );
    pathStr = pathStr.append( this->requestType() );
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
QString EveApiRequest::makeID( const QString& scope, int& id, const QMap<QString, QString>& parameters )
{
    QDateTime timeStamp = QDateTime::currentDateTime();
    QString idStr = timeStamp.toString( QString( "yyyyMMddhhmmsszzz" ) );
    idStr = idStr.append( "::" );
    idStr = idStr.append( this->path( scope ) );
    idStr = idStr.append( QString( "-%1" ).arg( id ) );
    idStr = idStr.append( "-" );
    idStr = idStr.append( parameters.value( "userID" ) );
    idStr = idStr.append( "-" );
    idStr = idStr.append( parameters.value( "characterID" ) );
    idStr = idStr.append( "-" );
    idStr = idStr.append( parameters.value( "apiKey" ) );
    return idStr;
}

/*!
Check the paramaters
*/
bool EveApiRequest::validateParamaters( const QMap<QString, QString>& parameters, QUrl& url )
{
//    std::cout << "EveApiRequest::validateParamaters()" << std::endl;
    //std::cout <<  << std::endl;
    QString paramID;
    // check all the required params
    foreach( paramID, this->_requiredParamaters )
    {
        QString param = parameters.value( paramID );
//        std::cout << paramID.toStdString() << ": " << param.toStdString() << std::endl;
        if ( param.isNull() )
            return false;
        url.addQueryItem( paramID, param );
    }
    // check optional parameters
    foreach( paramID, this->_optionalParameters )
    {
        QString param = parameters.value( paramID );
//        std::cout << paramID.toStdString() << ": " << param.toStdString() << std::endl;
        if ( !param.isNull() )
            url.addQueryItem( paramID, param );
    }
    return true;
}

/*!
Fetch from API
*/
QString EveApiRequest::fetchFromApi( const QString& host, const QString& scope,
                                     const QMap<QString, QString>& parameters,
                                     bool internal )
{
    int id = 0;

    QString idStr = QString();

    QString serverPath = this->path( scope );

    QUrl url( serverPath );
    if ( this->validateParamaters( parameters, url ) )
    {
        QHttpRequestHeader head( "POST", serverPath );
        head.setValue( "Host", host );
        head.setValue( "Content-type", "application/x-www-form-urlencoded" );

        QBuffer* data = new QBuffer;

        data->setData( url.encodedQuery() );

        this->_http->setHost( host );
        id = this->_http->request( head, data );

        this->_requestBuffers.insert( id, data );

        this->_requests.insert( id, qMakePair( scope, this->requestType() ) );

        idStr = makeID( scope, id, parameters );

        this->_id.insert( id, idStr );

        this->_internalRequest.insert( id, internal );

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
    if ( root.tagName() != "eveapi" )
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
        if ( firstLevel.toElement().tagName() == QString( "cachedUntil" ) )
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
    QStringList dateAndTime = timeString.split( " " );
    QStringList dateStrings = dateAndTime.at( 0 ).split( "-" );
    QStringList timeStrings = dateAndTime.at( 1 ).split( ":" );

    int year = dateStrings.at( 0 ).toInt();
    int month = dateStrings.at( 1 ).toInt();
    int day = dateStrings.at( 2 ).toInt();

    int hours = timeStrings.at( 0 ).toInt();
    int minutes = timeStrings.at( 1 ).toInt();
    int seconds = timeStrings.at( 2 ).toInt();

    QDate date( year, month, day );
    QTime time( hours, minutes, seconds );

    QDateTime dateTime( date, time, Qt::UTC );

    return dateTime;
}

/*!
remove expired cache files (related to the one that has been checked).

This is intended for use with journal/transaction walking, where
multiple cache files are created. If the journal is requested after
the cache has expired, then only the first file will be overwritten
(as the request that created the other files will not be repeated,
because different beforeRefID numbers will be used) and the others will
remain, and more may be created (if journal walking is used).

This method removes all related cache files when the first expires
(i.e. when /char/WalletJournal.xml expires, regular expressions are
used to find all other files in the /char/ scope that end with the text
"WalletJournal.xml", so that the other cache files are removed as well).
*/
void EveApiRequest::cleanCache( const QString& scope,
                                QMap<QString, QString>& parameters )
{
    QStringList cacheDirs = cachePath( scope, parameters );

    QString cachePathStr( QCoreApplication::applicationDirPath() );
    cachePathStr = cachePathStr.append( "/" );
    cachePathStr = cachePathStr.append( this->_dataPath );
    QString dir;
    foreach( dir, cacheDirs )
    {
        cachePathStr = cachePathStr.append( "/" );
        cachePathStr = cachePathStr.append( dir );
    }

    QDir cacheDir( cachePathStr );

    QStringList files = cacheDir.entryList();
    QString fileName;
    foreach( fileName, files )
    {
        if ( fileName.endsWith( this->_requestType ) )
        {
            QString file = cachePathStr;
            file = file.append( "/" );
            file = file.append( fileName );
            QFile::remove( file );
        }
    }
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

    QBuffer* buffer = this->_requestBuffers.take( id );
    QPair<QString, QString> request = this->_requests.take( id );
    QString scope = request.first;
    QString idStr = this->_id.take( id );
    QString response = this->_response.take( id );
    QMap<QString, QString> parameters = this->_paramaters.take( id );

    bool internal = this->_internalRequest.take( id );

    QByteArray data = this->_http->readAll();

    if ( error )
    {
        QString err = this->_http->errorString();
        //if ( internal )
        //{
        //    emit internalRequestFailed( idStr, err, response );
        //}
        //else
        //{
            emit requestFailed( idStr, err, response );
        //}
    }
    else
    {
        if ( !scope.isEmpty() )
        {
            QDir cwd( QCoreApplication::applicationDirPath() );
            if ( !cwd.exists( this->_dataPath ) )
            {
                cwd.mkdir( this->_dataPath );
            }
            cwd.cd( this->_dataPath );

            QStringList dirs = this->cachePath( scope, parameters );
            QString dir;
            foreach( dir, dirs )
            {
                if ( !cwd.exists( dir ) )
                {
                    cwd.mkdir( dir );
                }
                cwd.cd( dir );
            }

            QString thisCachePath = cwd.path();

            thisCachePath = thisCachePath.append( "/" );
            QString cacheID;
            foreach( cacheID, this->_fileIDParam )
            {
                thisCachePath = thisCachePath.append( parameters.value( cacheID ) );
            }
            thisCachePath = thisCachePath.append( this->requestType() );

            QDomDocument xmlData;
            xmlData.setContent( data );

            QDateTime cacheTime = getCacheTime( xmlData );

            QFile saveFile( thisCachePath );

            if ( saveFile.open( QIODevice::ReadWrite | QIODevice::Truncate ) )
            {
                QTextStream save( &saveFile );
                xmlData.save( save, this->_xmlIndent );
                saveFile.close();
            }
            if ( internal )
            {
                emit internalRequestComplete( idStr, xmlData, response, cacheTime );
            }
            else
            {
                emit requestComplete( idStr, xmlData, response, cacheTime );
            }
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
    QString response = QString( "%1 - " ).arg( head.statusCode() );
    response = response.append( head.reasonPhrase() );

    this->_response.insert( this->_currentRequest, response );
}
