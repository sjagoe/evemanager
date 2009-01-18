
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

#ifndef _EVEAPI_SCOPE_HH_
#define _EVEAPI_SCOPE_HH_

#include <QObject>
#include <QMap>
#include <QString>
#include <QDateTime>
#include <QMutex>

#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

class QDomDocument;

namespace EveApi
{
    class Request;

    class Scope: public QObject
    {
        Q_OBJECT;
    public:
        /*!
          create the child classes that provide API functionality
        */
        Scope( QString& host,
               QString& dataPath,
               int& xmlIndent,
               QString& scope,
               const int& proxyType,
               const QString & proxyHost,
               const quint16 & proxyPort,
               const QString & proxyUser,
               const QString & proxyPassword,
               QObject* parent = 0 );

        virtual ~Scope() {};

    public slots:
        /*!
          Set the proxy to use for http requests
        */
        void setProxy( const int& proxyType,
                       const QString& proxyHost,
                       const quint16& proxyPort,
                       const QString & proxyUser,
                       const QString & proxyPassword );

    protected:
        /*!
          Get the host of the API server
        */
        const QString& hostName();

        /*!
          Get the local data subdir
        */
        const QString& dataPath();

        /*!
          get the XML Indent amount
        */
        const int& xmlIndent();

        /*!
          get the current scope
        */
        const QString& scope();

        /*!
          Add a "Request Type" to the list
        */
        void addRequestType( QString& id, shared_ptr<Request> request );

        /*!
          Call a request of the specified type
        */
        QString request( QString& id, QMap<QString, QString>& parameters
                         /*, bool internal = false,
                           QString requestId = QString()*/ );

        /*!
          Create request objects
        */
        virtual void createRequest( QString& requestId,
                                    QStringList& requiredParams,
                                    QStringList& optionalParams,
                                    QStringList& cacheId,
                                    const int& p_type,
                                    const QString& host,
                                    const quint16& port,
                                    const QString & user,
                                    const QString & password ) = 0;

    private:
        //! QMutex to sync multiple access to the API
        QMutex _mutex;

        //! The API host server
        QString _hostName;

        //! The subdirectory in which to store cache
        QString _dataPath;

        //! amount to indent XML files when saved
        int _xmlIndent;

        //! Scope (i.e. server directory)
        QString _scope;

        //! QMap storing each of the possible requests in this scope
        QMap<QString, shared_ptr<Request> > _apiRequests;

        /*!
          return a previously added request type
        */
        shared_ptr<Request> requestType( QString& id ) const;

        /*!
          create all requests (delegated from the constructor)
        */
        virtual void createRequests( const int& proxyType,
                                     const QString & proxyHost,
                                     const quint16 & proxyPort,
                                     const QString & proxyUser,
                                     const QString & proxyPassword ) = 0;

    signals:
        void requestComplete( QString id, shared_ptr<QDomDocument> result,
                              QString httpResponse, QDateTime cacheExpireTime,
                              QString requestType  );
        void requestComplete( QString& id, QString& result,
                              QString& httpResponse, QDateTime& cacheExpireTime,
                              QString& requestType );
        void requestFailed( QString id, QString error, QString httpResponse );
    };
};

#endif
