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
