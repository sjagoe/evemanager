
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

#ifndef __EVEAPI_HH__
#define __EVEAPI_HH__

#include <QDateTime>
#include <QObject>
#include <QString>

#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

class QDomDocument;

namespace EveApi
{

    class Account;
    class Character;
    class Corporation;
    class Eve;
    class Map;
    class Scope;

    class EveApi: public QObject
    {
        Q_OBJECT;
    public:
        /*!
          set up the scopes of the API
        */
        EveApi( QString& hostName,
                QString& dataPath,
                const int& proxyType = 0,
                const QString& proxyHost = QString(),
                const quint16& proxyPort = 0,
                const QString & proxyUser = QString(),
                const QString & proxyPassword = QString(),
                QObject* parent = 0 );

        /*!
          provide access to areas of the api in the "/account/" context
        */
        Account& account();

        /*!
          provide access to areas of the api in the "/eve/" context
        */
        Eve& eve();

        /*!
          provide access to areas of the api in the "/map/" context
        */
        Map& map();

        /*!
          provide access to aread of the api in the "/char/" context
        */
        Character& character();

        /*!
          provide access to aread of the api in the "/corp/" context
        */
        Corporation& corp();

    public slots:
        /*!
          Set the proxy to use for http requests
        */
        void setProxy( const int& proxyType,
                       const QString& proxyHost,
                       const quint16& proxyPort,
                       const QString & proxyUser,
                       const QString & proxyPassword );

    private:
        //! API Server hostname
        QString _hostName;

        //! path to the data subdirectory
        QString _dataPath;

        //! amount to indent XML blocks when writing files
        int _xmlIndent;

        //! "/eve/" scope
        shared_ptr<Eve> _eve;

        //! "/map/" scope
        shared_ptr<Map> _map;

        //! "/char/" scope
        shared_ptr<Character> _char;

        //! "/corp/" scope
        shared_ptr<Corporation> _corp;

        shared_ptr<Account> _account;

        /*!
          create the scopes, and connect scope-specific signals and slots
        */
        void createScopes( const int& p_type,
                           const QString& host,
                           const quint16& port,
                           const QString & user,
                           const QString & password );

        /*!
          connect the signals of each scope member
        */
        void connectScope( shared_ptr<Scope> scope );

    signals:
        void requestComplete( QString id, shared_ptr<QDomDocument> result,
                              QString httpResponse, QDateTime cacheExpireTime,
                              QString requestType );
        void requestFailed( QString id, QString error, QString httpResponse );
    };
};

#endif
