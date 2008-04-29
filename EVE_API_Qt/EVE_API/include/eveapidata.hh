
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

#ifndef __EVEAPIDATA_HH__
#define __EVEAPIDATA_HH__

//#include <QSharedData>
//#include <QSharedDataPointer>

#include <QDateTime>

#include "eveapidatatype.hh"

class EveApiData
{
    public:
        /*!
        Call default constructors
        */
        EveApiData();

        /*!
        Create a data container of a specific type
        */
        EveApiData( ParsedDataType thisType );

        /*!
        Return the data type
        */
        const ParsedDataType& type() const;

        /*!
        Return the time that the api reports the file was fetched
        */
        const QDateTime& timeFetched() const;

        /*!
        Set the time fetched
        */
        void setTimeFetched( const QDateTime& dateTime );

        /*!
        Return the time that the cache expires
        */
        const QDateTime& cachedUntil() const;

        /*!
        Set the time that the cache expires
        */
        void setCachedUntil( const QDateTime& dateTime );

    private:
        //! The type of data that the object stores
        ParsedDataType _type;

        //! The time that the data was fetched from the API (as reported by the API)
        QDateTime _timeFetched;

        //! The time that the cache will expire (as reported by the API)
        QDateTime _cachedUntil;
};



#endif
