
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

#ifndef CHARACTERSPARSER_H
#define CHARACTERSPARSER_H

#include <QDateTime>
#include <QMap>
#include <QObject>
#include <QSharedPointer>
#include <QString>
#include <QStringList>
#include <QtXmlPatterns>

#include "abstracteveapidata.hh"
#include "charactersdata.h"
#include "delegate.h"

#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

namespace EveApi
{
    class CharactersParser: public Delegate
    {
        Q_OBJECT;
    public:
        CharactersParser( QObject* parent=0 );

        virtual void parse( QString& id, QString& data,
                            QString& httpResponse,
                            QDateTime& cacheExpireTime );

    private:
        QString getRowsetAttribute(QString& data, const char* attribute);

        QStringList getCharacterIds(QString& data, QString& key);

        int getApiVersion(QString& data);

    signals:
        void requestComplete( QString id, QSharedPointer<CharactersData> data,
                              QString httpResponse, QDateTime cacheExpiredTime );
    };
};

#endif // CHARACTERSPARSER_H
