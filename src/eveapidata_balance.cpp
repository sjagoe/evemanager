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
