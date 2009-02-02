
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

#ifndef DELEGATE_H
#define DELEGATE_H

#include <QDateTime>
#include <QObject>
#include <QSharedPointer>
#include <QString>
#include <QtXmlPatterns>

#include "charactersdata.h"

#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

namespace EveApi
{
    class Delegate: public QObject
    {
        Q_OBJECT;
    public:
        Delegate( QObject* parent=0 );

        /*!
          Public interface for parsing a the XML format from the API.
          It is assumed that the correct parser has been chosen for
          the data being parsed.
         */
        virtual void parse( const QString& id, const QString& data,
                            const QString& httpResponse,
                            const QDateTime& cacheExpireTime ) = 0;

    protected:
        /*
          Run an XQuery against some XML in a string.
         */
        bool runXQuery( const QString& query, const QString& data, QXmlResultItems& result );

        /*
          Helper function to get the values from a row.

          @arg rowsetName The unique name identifier of the rowset
          @arg key The name of the key column in the rowset
          @arg keyVal The value of the key to find the row
          @arg data The XML data in which to look up the values
          @arg columns A list of columns in the rowset for which to fetch data.
         */
        QMap<QString, QString> getRowDataByName(
                const QString& rowsetName, const QString& key, const QString& keyVal,
                const QString& data, const QStringList& columns );

        QDateTime getServerTime(const QString& data);

        QList<QVariant> getAtomicValues( const QString& query, const QString& data );

        QVariant getAtomicValue( const QString& query, const QString& data );

        QString runXQuery( const QString& query, const QString& data );
    };
}

#endif // DELEGATE_H
