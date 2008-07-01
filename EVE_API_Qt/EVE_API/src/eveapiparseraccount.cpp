
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

#include "eveapiparseraccount.hh"

#include "eveapiaccount.hh"

#include "eveapiparserthread_characters.hh"

/*!
call QThread constructor
*/
EveApiParserAccount::EveApiParserAccount( QString& host, QString& dataPath,
        int& xmlIndent, QString& scope, QObject* parent ) :
        QThread( parent )
{
    this->_eveApi.reset( new EveApiAccount( host, dataPath, xmlIndent, scope ) );
    connect( this->_eveApi.get(), SIGNAL( requestComplete( QString, shared_ptr<QDomDocument>, QString, QDateTime ) ),
             this, SLOT( apiRequestComplete( QString, shared_ptr<QDomDocument>, QString, QDateTime ) ) );
    connect( this->_eveApi.get(), SIGNAL( requestFailed( QString, QString, QString ) ),
             this, SIGNAL( requestFailed( QString, QString, QString ) ) );
}

/*!
create a new request for the account balance
*/
QString EveApiParserAccount::characters( QMap<QString, QString>& parameters )
{
    this->_apiMutex.lock();
    // create an API request
    QString requestId = this->_eveApi->characters( parameters );
    // map the ID to a parser
    this->_requestIdToParserMap.insert( requestId, PDT_CHARACTERLIST );
    this->_apiMutex.unlock();
    return requestId;
}

/*!
create actual parser objects, and start the event loop
*/
void EveApiParserAccount::run()
{
    this->setupParsers();
    this->exec();
}

/*!
Create and set up the parsers
*/
void EveApiParserAccount::setupParsers()
{
    // Character List Parser
    shared_ptr<EveApiParserThread> parser( new EveApiParserThreadCharacters );
    connect( this, SIGNAL( parseCharacters( QString, shared_ptr<QDomDocument> ) ),
             parser.get(), SLOT( parse( QString, shared_ptr<QDomDocument> ) ) );
    connect( parser.get(), SIGNAL( parsingComplete( QString, shared_ptr<EveApiDataCharacters> ) ),
             this, SIGNAL( charactersComplete( QString, shared_ptr<EveApiDataCharacters> ) ) );
    connect( parser.get(), SIGNAL( requestFailed( QString, QString, QString ) ),
             this, SIGNAL( requestFailed( QString, QString, QString ) ) );
    this->_parsers.insert( PDT_CHARACTERLIST, parser );
}

/*!
API request is complete (i.e. the XML has been received from the API
*/
void EveApiParserAccount::apiRequestComplete( QString requestId,
        shared_ptr<QDomDocument> xmlDocument,
        QString httpResponse,
        QDateTime cacheExpireTime )
{
    ParsedDataType type = this->_requestIdToParserMap.take( requestId );
    switch ( type )
    {
        case PDT_CHARACTERLIST:
        {
            emit parseCharacters( requestId, xmlDocument );
            break;
        }
        default:
        {
            // invalid type for this request mechanism
            break;
        }
    }
}

