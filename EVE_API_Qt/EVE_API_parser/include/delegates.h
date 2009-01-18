
/*
 * Copyright 2009 Simon Jagoe
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

#ifndef DELEGATES_H
#define DELEGATES_H

#include <QDateTime>
#include <QMap>
#include <QObject>
#include <QSharedPointer>
#include <QString>

#include "charactersdata.h"
#include "delegate.h"

#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

namespace EveApi
{
    /*!
      Class to look up parser delegates by API function.
     */
    class Delegates: public QObject
    {
        Q_OBJECT;
    public:
        /*!
          Construct the delegate mapper.
         */
        Delegates();

    public slots:
        /*!
          Handle a request for parsing the output of the EVE API.
         */
        void handleRequest( QString& id,
                            QString& data,
                            QString& httpResponse,
                            QDateTime& cacheExpireTime,
                            QString& requestType );

    private:
        /*!
          Map of API functions to delegates that are able to parse the output.
         */
        QMap<QString, QSharedPointer<Delegate> > _delegates;

    signals:
        /*!
          Signal to pass the parsed data back to the original
          caller. The request is identified by the unique request ID.
         */
        void requestComplete( QString id, QSharedPointer<CharactersData> data,
                              QString httpResponse, QDateTime cacheExpireTime );
    };
};

#endif // DELEGATES_H
