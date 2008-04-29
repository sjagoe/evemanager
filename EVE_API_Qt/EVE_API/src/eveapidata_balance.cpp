
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

#include "eveapidata_balance.hh"

EveApiDataBalance::EveApiDataBalance() :
    EveApiDataTable( PDT_ACCOUNTBALANCE )
{

}

/*!
Add Account
*/
void EveApiDataBalance::addAccount( int accountKey, QMap<QString, QString> rowData )
{
    if ( (accountKey >= 1000) && ( accountKey <= 1006 ) )
    {
        accountKey -= 1000;
    }
    if ( ( accountKey >= 0 ) && ( accountKey <= 6 ) )
    {
        this->_accounts.insert( accountKey, rowData );
    }
}

/*!
get the data stored in a row
*/
QMap<QString, QString> EveApiDataBalance::getRow( int accountKey )
{
    return this->_accounts.value( accountKey );
}
