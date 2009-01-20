
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

        virtual void parse( QString& id, QString& data,
                            QString& httpResponse,
                            QDateTime& cacheExpireTime ) = 0;

    protected:
        bool runXQuery( QString& query, QString& data, QXmlResultItems& result );

        QMap<QString, QString> getRowDataByName( QString& rowsetName, QString& key, QString& keyVal,
                                           QString& data, QStringList& columns );

        QDateTime getServerTime(QString& data);

        QList<QVariant> getAtomicValues( QString& query, QString& data );

        QVariant getAtomicValue( QString& query, QString& data );

        QString getXmlQueryResult( QString& query, QString& data );
    };
}

#endif // DELEGATE_H
