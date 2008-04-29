
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

#include <QObject>

#include <QString>

#include <boost/shared_ptr.hpp>

#include "eveapiaccount.hh"
#include "eveapieve.hh"
#include "eveapimap.hh"
#include "eveapicharacter.hh"
#include "eveapicorporation.hh"

using boost::shared_ptr;

class QDomDocument;

class EveApi: public QObject
{
        Q_OBJECT
    public:
        /*!
        set up the scopes of the API
        */
        EveApi( QString& dataPath,
                const int& proxyType = 0,
                const QString& proxyHost = QString(),
                const quint16& proxyPort = 0,
                const QString & proxyUser = QString(),
                const QString & proxyPassword = QString(),
                QObject* parent = 0 );

        /*!
        provide access to areas of the api in the "/account/" context
        */
        EveApiAccount& account();

        /*!
        provide access to areas of the api in the "/eve/" context
        */
        EveApiEve& eve();

        /*!
        provide access to areas of the api in the "/map/" context
        */
        EveApiMap& map();

        /*!
        provide access to aread of the api in the "/char/" context
        */
        EveApiCharacter& character();

        /*!
        provide access to aread of the api in the "/corp/" context
        */
        EveApiCorporation& corp();

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
        EveApiEve* _eve;

        //! "/map/" scope
        EveApiMap* _map;

        //! "/char/" scope
        EveApiCharacter* _char;

        //! "/corp/" scope
        EveApiCorporation* _corp;

        EveApiAccount* _account;

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
        void connectScope( EveApiScope* scope );

    signals:
        void requestComplete( QString id, shared_ptr<QDomDocument> result, QString httpResponse, QDateTime );
        void requestFailed( QString id, QString error, QString httpResponse );
};

#endif
