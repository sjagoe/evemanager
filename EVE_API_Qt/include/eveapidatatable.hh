
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

#ifndef __EVEAPIDATATABLE_HH__
#define __EVEAPIDATATABLE_HH__

#include <QString>
#include <QStringList>

#include "eveapidata.hh"

class EveApiDataTable: public EveApiData
{
    public:
        /*!
        Call default constructors
        */
        EveApiDataTable();

        /*!
        Create a table of a specific type
        */
        EveApiDataTable( ParsedDataType thisType );

        /*!
        Get the table name
        */
        const QString& name() const;

        /*!
        Set the table name
        */
        void setName( const QString& name );

        /*!
        Get the table key
        */
        const QString& key() const;

        /*!
        Set the table key
        */
        void setKey( const QString& key );

        /*!
        Get the list of columns
        */
        const QStringList& columns() const;

        /*!
        Set the list of columns
        */
        void setColumns( const QStringList& columns );

    private:
        //! The name of the "rowset" in the XML
        QString _tableName;

        //! The key of the table
        QString _tableKey;

        //! A List of column titles
        QStringList _tableColumns;
};

#endif
