#include "eveapi.hh"


/*!
set up the scopes of the API
*/
EveApi::EveApi( QString& dataPath,
                const int& proxyType,
                const QString & proxyHost,
                const quint16 & proxyPort,
                const QString & proxyUser,
                const QString & proxyPassword,
                QObject * parent ) :
        QObject( parent ),
        _hostName( "api.eve-online.com" ),
        _dataPath( dataPath ),
        _xmlIndent( 4 )
{
//    //! API Server hostname
//    this->_hostName = "api.eve-online.com";
//
//    //! path to the data subdirectory
//    this->_dataPath = dataPath;
//
//    //! amount to indent XML blocks when writing files
//    this->_xmlIndent = 4;

    this->createScopes( proxyType, proxyHost, proxyPort, proxyUser,
                        proxyPassword );
}

/*!
provide access to areas of the api in the "/account/" context
*/
EveApiAccount& EveApi::account()
{
    return ( *this->_account );
}

/*!
provide access to areas of the api in the "/eve/" context
*/
EveApiEve& EveApi::eve()
{
    return ( *this->_eve );
}

/*!
provide access to areas of the api in the "/map/" context
*/
EveApiMap& EveApi::map()
{
    return ( *this->_map );
}

/*!
provide access to aread of the api in the "/char/" context
*/
EveApiCharacter& EveApi::character()
{
    return ( *this->_char );
}

/*!
provide access to aread of the api in the "/corp/" context
*/
EveApiCorporation& EveApi::corp()
{
    return ( *this->_corp );
}

/*!
create the scopes, and connect scope-specific signals and slots
*/
void EveApi::createScopes( const int& proxyType,
                           const QString & proxyHost,
                           const quint16 & proxyPort,
                           const QString & proxyUser,
                           const QString & proxyPassword )
{
    // "account" scope
    QString scope = "account";
    this->_account = new EveApiAccount( this->_hostName, this->_dataPath,
                                        this->_xmlIndent, scope, proxyType,
                                        proxyHost, proxyPort, proxyUser,
                                        proxyPassword );
    this->connectScope( this->_account );

    // "eve" scope
    scope = "eve";
    this->_eve = new EveApiEve( this->_hostName, this->_dataPath,
                                this->_xmlIndent, scope, proxyType,
                                proxyHost, proxyPort, proxyUser,
                                proxyPassword );
    this->connectScope( this->_eve );

    // "map" scope
    scope = "map";
    this->_map = new EveApiMap( this->_hostName, this->_dataPath,
                                this->_xmlIndent, scope, proxyType,
                                proxyHost, proxyPort, proxyUser,
                                proxyPassword );
    this->connectScope( this->_map );

    // "char" scope
    scope = "char";
    this->_char = new EveApiCharacter( this->_hostName, this->_dataPath,
                                       this->_xmlIndent, scope, proxyType,
                                       proxyHost, proxyPort, proxyUser,
                                       proxyPassword );
    this->connectScope( this->_char );

    // "corp" scope
    scope = "corp";
    this->_corp = new EveApiCorporation( this->_hostName, this->_dataPath,
                                         this->_xmlIndent, scope, proxyType,
                                         proxyHost, proxyPort, proxyUser,
                                         proxyPassword );
    this->connectScope( this->_corp );
}

/*!
connect the signals of each scope member
*/
void EveApi::connectScope( EveApiScope* scope )
{
    connect( scope,
             SIGNAL( requestComplete( QString, shared_ptr<QDomDocument>, QString, QDateTime ) ),
             this, SIGNAL( requestComplete( QString, shared_ptr<QDomDocument>, QString, QDateTime ) ) );
    connect( scope,
             SIGNAL( requestFailed( QString, QString, QString ) ),
             this, SIGNAL( requestFailed( QString, QString, QString ) ) );
}
