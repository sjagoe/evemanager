
/*
 * Copyright 2007-2009 Simon Jagoe
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

#ifndef _EVEAPI_PARSER_HH_
#define _EVEAPI_PARSER_HH_

#include <QObject>
#include <QSharedPointer>
#include <QString>

#include "charactersdata.h"
#include "delegates.h"

#include "eveapi.hh"
#include "eveapiaccount.hh"
#include "eveapicharacter.hh"
#include "eveapicorporation.hh"
#include "eveapieve.hh"
#include "eveapimap.hh"

#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

namespace EveApi
{

    class Parser: public QObject
    {
        Q_OBJECT;

    public:
        /*!
          Construct a new Parser
        */
        Parser( QString& hostName,
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


    private:
        //! The API module used to interact with the EVE API
        QSharedPointer<EveApi> _api;

        //! Object to delegate parsing to the correct parser
        QSharedPointer<Delegates> _delegates;

    signals:
        /*!
          Signal emitted when a character list request has been completed
         */
        void requestComplete( QString id, QSharedPointer<CharactersData> data,
                              QString httpResponse, QDateTime cacheExpireTime,
                              QString requestType );
    };
};

#endif
