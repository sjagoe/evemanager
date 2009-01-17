
/*
 * Copyright 2007-2008 Simon Jagoe
 *
 * This file is part of EVE_API_Qt.
 *
 * EVE_API_Qt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EVE_API_Qt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EVE_API_Qt.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "eveapirequest.hh"

#include <QCoreApplication>

#include <QHttp>
#include <QNetworkProxy>
#include <QBuffer>
#include <QDomDocument>

#include <QFile>
#include <QTextStream>

class RetrieveCacheException {};

EveApi::Request::Request( const QString& requestType,
                          const QString& dataPath,
                          const int& xmlIndent,
                          const QList<QString>& requiredParams,
                          const QList<QString>& optionalParams,
                          const QList<QString>& fileIDParam,
                          const int& p_type,
                          const QString& host,
                          const quint16& port,
                          const QString & user,
                          const QString & password,
                          QObject* parent )
    : QObject( parent )
{
    this->_http.reset( new QHttp );
    this->setProxy( p_type, host, port, user, password );
    this->_requestType = requestType;
    this->_dataPath = dataPath;
    this->_xmlIndent = xmlIndent;
    this->_requiredParamaters = requiredParams;
    this->_optionalParameters = optionalParams;
    this->_fileIDParam = fileIDParam;
    this->_currentRequest = 0;

    connect( this->_http.get(), SIGNAL( requestStarted( int ) ),
             this, SLOT( requestStarted( int ) ) );

    connect( this->_http.get(), SIGNAL( requestFinished( int, bool ) ),
             this, SLOT( requestFinished( int, bool ) ) );

    connect( this->_http.get(),
             SIGNAL( responseHeaderReceived( QHttpResponseHeader ) ),
             this, SLOT( responseHeaderReceived( QHttpResponseHeader ) ) );
}

/*!
  Add a request to be handled.

  \return unique request identifier (used to id a completed request)
*/
QString EveApi::Request::addRequest( const QString& host,
                                     const QString& scope,
                                     QMap<QString, QString>& parameters )
{
    QString idStr = QString();

    try
    {
        idStr = this->getFromCache( host, scope, parameters );
    }
    catch (RetrieveCacheException e)
    {
        idStr = this->fetchFromApi( host, scope, parameters );
    }

    return idStr;
}

/*!
  Try to get a document from cache, raise if not possible
*/
QString EveApi::Request::getFromCache( const QString& host,
                                       const QString& scope,
                                       QMap<QString, QString>& parameters )
{
    QString cachePathStr = this->buildCachePath( scope, parameters );

    shared_ptr<QDomDocument> cacheDom( new QDomDocument );

    QFile loadFile( cachePathStr );
    if ( loadFile.open( QIODevice::ReadOnly ) )
    {
        if ( cacheDom->setContent( &loadFile ) )
        {
            loadFile.close();
            // file loaded
            QDateTime cacheTime = this->getCacheTime( cacheDom );
            QDateTime now = QDateTime::currentDateTime();
            QDateTime nowUTC = now.toUTC();
            // over by 60 secs, prevent accidental fetch if the cache has not
            // expired (due to differences in clocks)
            if ( nowUTC.secsTo( cacheTime ) >= -60 )
            {
                int idi = 0;
                QString idStr = this->makeID( scope, idi, parameters );
                emit requestComplete( idStr, cacheDom,
                                      QString( "FROM LOCAL CACHE" ),
                                      cacheTime, this->requestType() );
                return idStr;
            }
        }
        else
        {
            loadFile.close();
        }
    }
    this->cleanCache( scope, parameters );
    throw RetrieveCacheException();
}


/*!
  Set the proxy to use for http requests
*/
void EveApi::Request::setProxy( const int& p_type,
                                const QString & host,
                                const quint16 & port,
                                const QString & user,
                                const QString & password )
{
    if ( this->_http )
    {
        QNetworkProxy::ProxyType proxyType = QNetworkProxy::NoProxy;
        switch ( p_type )
        {
        case 1:
            {
                proxyType = QNetworkProxy::HttpProxy;
                break;
            }
        case 2:
            {
                proxyType = QNetworkProxy::Socks5Proxy;
                break;
            }
        }
        QNetworkProxy proxy( proxyType, host, port, user, password );
        this->_http->setProxy( proxy );
    }
}

// /*!
//Add an internal request to be handled.
//
//\return unique request identifier (used to id a completed request)
//*/
//QString EveApi::Request::addInternalRequest( const QString& host,
//        const QString& scope,
//        QMap<QString, QString>& parameters )
//{
//    this->addRequest( host, scope, parameters, true );
//}

/*!
  return the server path (URI) to access the requested information
*/
QString EveApi::Request::path( const QString& scope )
{
    QString pathStr = "/";
    pathStr = pathStr.append( scope );
    pathStr = pathStr.append( "/" );
    pathStr = pathStr.append( this->requestType() );
    pathStr = pathStr.append( QString( this->fileExtension() ) );
    return pathStr;
}

const QString& EveApi::Request::requestType() const
{
    return this->_requestType;
}

/*!
  make a unique string ID
*/
QString EveApi::Request::makeID(
    const QString& scope, int& id, const QMap<QString, QString>& parameters )
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
  Return the QDir representing the directory that cache for
  this request will be stored in. Raises RetrieveCacheException if
  the directory does not exist and create is not True.
*/
QDir EveApi::Request::buildCacheDir(
    const QString& scope, const QMap<QString, QString>& parameters,
    bool create )
{
    QStringList cacheDirs = cachePath( scope, parameters );
    QDir cachePath( QCoreApplication::applicationDirPath() );
    if (! cachePath.cd( this->_dataPath ) )
    {
        if ( create )
        {
            cachePath.mkdir( this->_dataPath );
            cachePath.cd( this->_dataPath );
        }
        else
        {
            throw RetrieveCacheException();
        }
    }
    QString dir;
    foreach( dir, cacheDirs )
    {
        if (! cachePath.cd( dir ) )
        {
            if ( create )
            {
                cachePath.mkdir( dir );
                cachePath.cd( dir );
            }
            else
            {
                throw RetrieveCacheException();
            }
        }
    }
    return cachePath;
}

/*!
  Return the absolute path to the cache file to be used to cache
  the request. Raises RetrieveCacheException if the directory does
  not exist and create is not True.
*/
QString EveApi::Request::buildCachePath(
    const QString& scope, const QMap<QString, QString>& parameters,
    bool create )
{
    QDir cachePath = this->buildCacheDir( scope, parameters, create );

    QString cacheFileStr("");

    QString cacheID;
    foreach( cacheID, this->_fileIDParam )
    {
        cacheFileStr = cacheFileStr.append( parameters.value( cacheID ) );
    }
    cacheFileStr = cacheFileStr.append( this->requestType() );

    return cachePath.absoluteFilePath(cacheFileStr);
}

/*!
  Check the paramaters
*/
bool EveApi::Request::validateParamaters(
    const QMap<QString, QString>& parameters, QUrl& url )
{
    //    std::cout << "EveApi::Request::validateParamaters()" << std::endl;
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
QString EveApi::Request::fetchFromApi(
    const QString& host, const QString& scope,
    const QMap<QString, QString>& parameters )
{
    int id = 0;

    //    QString idStr = oldId;
    QString idStr;

    QString serverPath = this->path( scope );

    QUrl url( serverPath );
    if ( this->validateParamaters( parameters, url ) )
    {
        QHttpRequestHeader head( "POST", serverPath );
        head.setValue( "Host", host );
        head.setValue( "Content-type", "application/x-www-form-urlencoded" );

        shared_ptr<QBuffer> data( new QBuffer );

        data->setData( url.encodedQuery() );

        this->_http->setHost( host );
        id = this->_http->request( head, data.get() );

        this->_requestBuffers.insert( id, data );

        this->_requests.insert( id, qMakePair( scope, this->requestType() ) );

        if ( idStr.isNull() )
            idStr = makeID( scope, id, parameters );

        this->_id.insert( id, idStr );

        //        this->_internalRequest.insert( id, internal );

        this->_paramaters.insert( id, parameters );
    }
    return idStr;
}

/*!
  Get the time that the cache expires from a QDomDocument
*/
//QDateTime EveApi::Request::getCacheTime( const QDomDocument& xmlDocument )
QDateTime EveApi::Request::getCacheTime( shared_ptr<QDomDocument> xmlDocument )
{
    QString currentTimeString;
    QString cachedUntilString;
    QDateTime cachedUntil;
    QDomElement root = xmlDocument->documentElement();
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
QDateTime EveApi::Request::eveApiTimeToQDateTime( QString timeString )
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
void EveApi::Request::cleanCache( const QString& scope,
                                  QMap<QString, QString>& parameters )
{
    try
    {
        QDir cacheDir = buildCacheDir( scope, parameters );
        QStringList files = cacheDir.entryList();
        QString fileName;
        foreach( fileName, files )
        {
            if ( fileName.endsWith( this->_requestType ) )
            {
                QString file = cacheDir.relativeFilePath( fileName );
                QFile::remove( file );
            }
        }
    }
    catch (RetrieveCacheException e)
    {
    }
}

/*!
  signal that a request has begun
*/
void EveApi::Request::requestStarted( int id )
{
    this->_currentRequest = id;
}

/*!
  signal that a request has finished so that the result can be delivered
*/
void EveApi::Request::requestFinished( int id, bool error )
{
    //    std::cout << "EveApi::Request::requestFinished()" << std::endl;
    this->_currentRequest = 0;

    shared_ptr<QBuffer> buffer = this->_requestBuffers.take( id );
    QPair<QString, QString> request = this->_requests.take( id );
    QString scope = request.first;
    QString idStr = this->_id.take( id );
    QString response = this->_response.take( id );
    QMap<QString, QString> parameters = this->_paramaters.take( id );

    //    bool internal = this->_internalRequest.take( id );

    QByteArray data = this->_http->readAll();

    if ( error )
    {
        QString err = this->_http->errorString();
        emit requestFailed( idStr, err, response );
    }
    else
    {
        if ( !scope.isEmpty() )
        {
            QString thisCachePath = this->buildCachePath( scope, parameters,
                                                          true );
            shared_ptr<QDomDocument> xmlData( new QDomDocument );
            xmlData->setContent( data );

            QDateTime cacheTime = getCacheTime( xmlData );

            QFile saveFile( thisCachePath );

            if ( saveFile.open( QIODevice::ReadWrite | QIODevice::Truncate ) )
            {
                QTextStream save( &saveFile );
                xmlData->save( save, this->_xmlIndent );
                saveFile.close();
            }
            emit requestComplete( 
                idStr, xmlData, response, cacheTime, this->requestType() );
        }
    }
}

/*!
  An http response is received
*/
void EveApi::Request::responseHeaderReceived( QHttpResponseHeader head )
{
    QString response = QString( "%1 - " ).arg( head.statusCode() );
    response = response.append( head.reasonPhrase() );

    this->_response.insert( this->_currentRequest, response );
}
