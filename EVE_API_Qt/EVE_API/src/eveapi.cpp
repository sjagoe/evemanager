
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

#include "eveapi.hh"

#include "eveapiaccount.hh"
#include "eveapicharacter.hh"
#include "eveapicorporation.hh"
#include "eveapieve.hh"
#include "eveapimap.hh"


/*!
  set up the scopes of the API
*/
EveApi::EveApi::EveApi( QString& hostName,
                        QString& dataPath,
                        const int& proxyType,
                        const QString & proxyHost,
                        const quint16 & proxyPort,
                        const QString & proxyUser,
                        const QString & proxyPassword,
                        QObject * parent ) :
    QObject( parent ),
    _hostName( hostName ),
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
EveApi::Account& EveApi::EveApi::account()
{
    return ( *this->_account );
}

/*!
  provide access to areas of the api in the "/eve/" context
*/
EveApi::Eve& EveApi::EveApi::eve()
{
    return ( *this->_eve );
}

/*!
  provide access to areas of the api in the "/map/" context
*/
EveApi::Map& EveApi::EveApi::map()
{
    return ( *this->_map );
}

/*!
  provide access to aread of the api in the "/char/" context
*/
EveApi::Character& EveApi::EveApi::character()
{
    return ( *this->_char );
}

/*!
  provide access to aread of the api in the "/corp/" context
*/
EveApi::Corporation& EveApi::EveApi::corp()
{
    return ( *this->_corp );
}

/*!
  Set the proxy to use for http requests
*/
void EveApi::EveApi::setProxy( const int& proxyType,
                               const QString& proxyHost,
                               const quint16& proxyPort,
                               const QString & proxyUser,
                               const QString & proxyPassword )
{
    this->_eve->setProxy(proxyType, proxyHost, proxyPort, proxyUser,
                         proxyPassword);
    this->_map->setProxy(proxyType, proxyHost, proxyPort, proxyUser,
                         proxyPassword);
    this->_char->setProxy(proxyType, proxyHost, proxyPort, proxyUser,
                          proxyPassword);
    this->_corp->setProxy(proxyType, proxyHost, proxyPort, proxyUser,
                          proxyPassword);
    this->_account->setProxy(proxyType, proxyHost, proxyPort, proxyUser,
                             proxyPassword);
}

/*!
  create the scopes, and connect scope-specific signals and slots
*/
void EveApi::EveApi::createScopes( const int& proxyType,
                                   const QString & proxyHost,
                                   const quint16 & proxyPort,
                                   const QString & proxyUser,
                                   const QString & proxyPassword )
{
    // "account" scope
    QString scope = "account";
    this->_account.reset(new Account( this->_hostName, this->_dataPath,
                                      this->_xmlIndent, scope, proxyType,
                                      proxyHost, proxyPort, proxyUser,
                                      proxyPassword ));
    this->connectScope( this->_account );

    // "eve" scope
    scope = "eve";
    this->_eve.reset(new Eve( this->_hostName, this->_dataPath,
                              this->_xmlIndent, scope, proxyType,
                              proxyHost, proxyPort, proxyUser,
                              proxyPassword ));
    this->connectScope( this->_eve );

    // "map" scope
    scope = "map";
    this->_map.reset(new Map( this->_hostName, this->_dataPath,
                              this->_xmlIndent, scope, proxyType,
                              proxyHost, proxyPort, proxyUser,
                              proxyPassword ));
    this->connectScope( this->_map );

    // "char" scope
    scope = "char";
    this->_char.reset(new Character( this->_hostName, this->_dataPath,
                                     this->_xmlIndent, scope, proxyType,
                                     proxyHost, proxyPort, proxyUser,
                                     proxyPassword ));
    this->connectScope( this->_char );

    // "corp" scope
    scope = "corp";
    this->_corp.reset(new Corporation( this->_hostName, this->_dataPath,
                                       this->_xmlIndent, scope, proxyType,
                                       proxyHost, proxyPort, proxyUser,
                                       proxyPassword ));
    this->connectScope( this->_corp );
}

/*!
  connect the signals of each scope member
*/
void EveApi::EveApi::connectScope( shared_ptr<Scope> scope )
{
    connect( scope.get(),
             SIGNAL( requestComplete( QString, shared_ptr<QDomDocument>,
                                      QString, QDateTime, QString ) ),
             this, SIGNAL( requestComplete( QString, shared_ptr<QDomDocument>,
                                            QString, QDateTime, QString ) ) );
    connect( scope.get(),
             SIGNAL( requestFailed( QString, QString, QString ) ),
             this, SIGNAL( requestFailed( QString, QString, QString ) ) );
}
