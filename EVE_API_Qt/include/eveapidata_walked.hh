
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

#ifndef __EVEAPIDATA_WALKED_HH__
#define __EVEAPIDATA_WALKED_HH__

#include <QList>
#include <QMap>
#include <QString>

#include <QSharedData>
#include <QSharedDataPointer>

#include "eveapidata.hh"

class EveApiDataWalkedData: public QSharedData
{
    public:
        EveApiDataWalkedData();
        EveApiDataWalkedData( const EveApiDataWalkedData& other );
        ~EveApiDataWalkedData();

        QList<QMap<QString, QString> > data;
};

class EveApiDataWalked: public EveApiData
{
    public:
        EveApiDataWalked();

        const QList<QMap<QString, QString> >& data() const;

        void appendData( const QList<QMap<QString, QString> >& newData );

        void appendData( const QMap<QString, QString>& newData );

    private:
        QSharedDataPointer<EveApiDataWalkedData> _data;
};

#endif
