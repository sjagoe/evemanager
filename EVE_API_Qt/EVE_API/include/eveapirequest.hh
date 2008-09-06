
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

#ifndef __EVEAPIREQUEST_HH__
#define __EVEAPIREQUEST_HH__

#include <QObject>

#include <QDir>
//#include <QHttp>
#include <QHttpResponseHeader>
#include <QMap>
#include <QPair>
#include <QString>
//#include <QDomDocument>
#include <QString>
#include <QUrl>
#include <QStringList>
#include <QDateTime>
#include <QList>

#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

class QHttp;
class QBuffer;
class QDomDocument;

class EveApiRequest: public QObject
{
    Q_OBJECT
    public:
    /*!
      Contructor, calls super-class constructor, creates dynamic objects
    */
    EveApiRequest( const QString& requestType,
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
                   QObject* parent=0 );
    
    virtual ~EveApiRequest() {};
    
    /*!
      Add a request to be handled.
      
      \return unique request identifier (used to id a completed request)
    */
    QString addRequest( const QString& host, const QString& scope,
                        QMap<QString, QString>& parameters
                        /*,
                          bool internal, QString oldId = QString()*/ );
    
    /*!
      Try to get a document from cache, raise if not possible
    */
    QString getFromCache( const QString& host,
                          const QString& scope,
                          QMap<QString, QString>& parameters );
    
    /*!
      Set the proxy to use for http requests
    */
    void setProxy( const int& p_type,
                   const QString& host,
                   const quint16& port,
                   const QString & user,
                   const QString & password );

//        /*!
//        Add an internal request to be handled.
//
//        \return unique request identifier (used to id a completed request)
//        */
//        QString addInternalRequest( const QString& host, const QString& scope,
//                            QMap<QString, QString>& parameters );

protected:
    /*!
      return the file extension (.aspx)
    */
    static const char* fileExtension()
    {
        return ".aspx";
    };

    /*!
      return the server path (URI) to access the requested information
    */
    QString path( const QString& scope );

    /*!
      return the requestType
    */
    const QString& requestType() const;

    /*!
      make a unique string ID
    */
    QString makeID( const QString& scope,
                    int& id,
                    const QMap<QString, QString>& parameters );

private:
    //! amount to indent blocks of XML
    int _xmlIndent;

    //! currently active request
    int _currentRequest;

    //! Filename on the server (excluding ".aspx")
    QString _requestType;

    //! local sub-directory in which to cache data
    QString _dataPath;

    //! HTTP object that performs requests to the EVE API
    shared_ptr<QHttp> _http;

    //! QMap mapping request IDs to buffers
    QMap<int, shared_ptr<QBuffer> > _requestBuffers;

    //! QMap mapping IDs to readable requests (QPair<scope, file>)
    QMap<int, QPair<QString, QString> > _requests;

    //! QMap mapping http id to a unique QString ID
    QMap<int, QString> _id;

    //        //! QMap to store if a request is internal or external
    //        QMap<int, bool> _internalRequest;

    //! QMap of the request and HTTP response
    QMap<int, QString> _response;

    //! QMap of character identifiers
    QMap<int, QMap<QString, QString> > _paramaters;

    //! required api function parameters
    QList<QString> _requiredParamaters;

    //! optional api function parameters
    QList<QString> _optionalParameters;

    /*!
      API params that will allow the cache file to be identified
      (where there could be more than one with the same name, such as when
      journal walking)
    */
    QList<QString> _fileIDParam;

    /*! 
      Return the QDir representing the directory that cache for
      this request will be stored in. Raises RetrieveCacheException if
      the directory does not exist and create is not True.
    */
    QDir buildCacheDir( const QString& scope,
                        const QMap<QString, QString>& parameters,
                        bool create=false );

    /*!
      Return the absolute path to the cache file to be used to cache
      the request. Raises RetrieveCacheException if the directory does
      not exist and create is not True.
    */
    QString buildCachePath( const QString& scope,
                            const QMap<QString, QString>& parameters,
                            bool create=false );

    /*!
      Check the paramaters
    */
    bool validateParamaters( const QMap<QString, QString>& parameters,
                             QUrl& url );

    /*!
      return a QStringList of filesystem directories,
      relative to the data directory, in which to store cache
    */
    virtual QStringList cachePath( const QString& scope,
                                   const QMap<QString, QString>& parameters ) = 0;

    /*!
      Fetch from API
    */
    QString fetchFromApi( const QString& host, const QString& scope,
                          const QMap<QString, QString>& parameters
                          /*,
                            bool internal, QString oldId = QString()*/ );
    
    /*!
      Get the time that the cache expires from a QDomDocument
    */
    //QDateTime getCacheTime( const QDomDocument& xmlDocument );
    QDateTime getCacheTime( shared_ptr<QDomDocument> xmlDocument );

    /*!
      convert a time specified in the API XML output to a QDateTime
    */
    QDateTime eveApiTimeToQDateTime( QString timeString );

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
    void cleanCache( const QString& scope,
                     QMap<QString, QString>& parameters );

private slots:
    /*!
      signal that a request has begun
    */
    void requestStarted( int id );

    /*!
      signal that a request has finished so that the result can be delivered
    */
    void requestFinished( int id, bool error );

    /*!
      An http response is received
    */
    void responseHeaderReceived( QHttpResponseHeader head );

signals:
    void requestComplete( QString id,
                          shared_ptr<QDomDocument> result,
                          QString httpResponse,
                          QDateTime cacheExpireTime );

    void requestFailed( QString id,
                        QString error,
                        QString httpResponse );

    //void internalRequestComplete( QString id, QDomDocument result, QString httpResponse, QDateTime cacheExpireTime );
    //void internalRequestFailed( QString id, QString error, QString httpResponse );
};



#endif
