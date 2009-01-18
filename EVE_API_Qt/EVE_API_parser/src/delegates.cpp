
/*
 * Copyright 2009 Simon Jagoe
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

#include "delegates.h"

#include "delegate.h"
#include "charactersparser.h"

EveApi::Delegates::Delegates()
{
    QSharedPointer<Delegate> delegate(new CharactersParser(this));
    this->connect(delegate.data(), SIGNAL(requestComplete(QString,QSharedPointer<CharactersData>,QString,QDateTime)),
                  this, SIGNAL(requestComplete(QString,QSharedPointer<CharactersData>,QString,QDateTime)));
    this->_delegates.insert("Characters.xml", delegate);
}

void EveApi::Delegates::handleRequest( QString id, shared_ptr<QDomDocument> data,
                                       QString httpResponse, QDateTime cacheExpireTime,
                                       QString requestType )
{
    QSharedPointer<Delegate> parser = this->_delegates.value( requestType );
    parser->parse( id, data, httpResponse, cacheExpireTime );
}