#ifndef __EVEAPIDATA_BALANCE_HH__
#define __EVEAPIDATA_BALANCE_HH__

#include "eveapidatatable.hh"

#include <QMap>
#include <QString>

class EveApiDataBalance: public EveApiDataTable
{
    public:
        /*!
        construct the data container for account balance
        */
        EveApiDataBalance();

        /*!
        Add Account
        */
        void addAccount( int accountKey, QMap<QString, QString> rowData );

        /*!
        get the data stored in a row
        */
        QMap<QString, QString> getRow( int accountKey = 0 );

    private:
        //! Data stored in the table, keyed by accountKey
        QMap<int, QMap<QString, QString> > _accounts;
};

#endif
