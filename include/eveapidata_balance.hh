
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
