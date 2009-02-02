
/*
 * Copyright 2007-2009 Simon Jagoe
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

#include "eveapiparser.hh"

#include "eveapi.hh"

EveApi::Parser::Parser( QString& hostName,
                        QString& dataPath,
                        const int& proxyType,
                        const QString & proxyHost,
                        const quint16 & proxyPort,
                        const QString & proxyUser,
                        const QString & proxyPassword,
                        QObject * parent ):
QObject(parent)
{
    this->_api = shared_ptr<EveApi>(
            new EveApi(hostName, dataPath, proxyType, proxyHost, proxyPort, proxyUser, proxyPassword, this));
    this->_delegates = shared_ptr<Delegates>(
            new Delegates());
    this->connect(this->_api.get(), SIGNAL(requestComplete( QString&, QString&, QString&, QDateTime&, QString&)),
                  this->_delegates.get(), SLOT(handleRequest( QString&, QString&, QString&, QDateTime&, QString&)));
    this->connect(this->_delegates.get(), SIGNAL(requestComplete(QString,shared_ptr<CharactersData>,QString,QDateTime)),
                  this, SIGNAL(requestComplete(QString,shared_ptr<CharactersData>,QString,QDateTime)));
}


EveApi::Account& EveApi::Parser::account()
{
    return this->_api->account();
}


EveApi::Eve& EveApi::Parser::eve()
{
    return this->_api->eve();
}


EveApi::Map& EveApi::Parser::map()
{
    return this->_api->map();
}


EveApi::Character& EveApi::Parser::character()
{
    return this->_api->character();
}


EveApi::Corporation& EveApi::Parser::corp()
{
    return this->_api->corp();
}

