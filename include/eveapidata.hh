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
