#include "eveapi.hh"

/*!
set up the scopes of the API
*/
EveApi::EveApi( QObject* parent )
    : QObject( parent )
{
    //! API Server hostname
    this->_hostName = "api.eve-online.com";

    //! path to the data subdirectory
    this->_dataPath = "data";

    //! amount to indent XML blocks when writing files
    this->_xmlIndent = 4;

    // "eve" scope
    QString scope = "eve";

    this->_eve = new EveApiEve( this->_hostName, this->_dataPath,
        this->_xmlIndent, scope );
    connect( this->_eve,
        SIGNAL(requestComplete( QString, QDomDocument, QString )),
        this, SIGNAL(requestComplete( QString, QDomDocument, QString )) );
    connect( this->_eve,
        SIGNAL(requestFailed( QString, QString, QString )),
        this, SIGNAL(requestFailed( QString, QString, QString )) );

    // "map" scope

    scope = "map";
    this->_map = new EveApiMap( this->_hostName, this->_dataPath,
        this->_xmlIndent, scope );
    connect( this->_map,
        SIGNAL(requestComplete( QString, QDomDocument, QString )),
        this, SIGNAL(requestComplete( QString, QDomDocument, QString )) );
    connect( this->_map,
        SIGNAL(requestFailed( QString, QString, QString )),
        this, SIGNAL(requestFailed( QString, QString, QString )) );
}

/*!
provide access to areas of the api in the "/eve/" context
*/
EveApiEve* EveApi::eve()
{
    return this->_eve;
}

/*!
provide access to areas of the api in the "/map/" context
*/
EveApiMap* EveApi::map()
{
    return this->_map;
}
