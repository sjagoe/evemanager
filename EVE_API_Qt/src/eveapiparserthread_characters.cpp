
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

#include "eveapiparserthread_characters.hh"

#include <QMetaType>
#include <QDomNode>
#include <QDomElement>

#include <QDomDocument>

#include "eveapidata_characters.hh"

/*!
Construct the parser
*/
EveApiParserThreadCharacters::EveApiParserThreadCharacters( QObject* parent ) :
        EveApiParserThread( PDT_CHARACTERLIST, parent )
{
    qRegisterMetaType<shared_ptr<EveApiDataCharacters> >( "shared_ptr<EveApiDataCharacters>" );
}

/*!
Perform the actual parsing of the data, and emit a signal when done.
The signal must be defined in the subclass
*/
void EveApiParserThreadCharacters::doParse( const QString& parserId,
        const shared_ptr<QDomDocument> doc )
{
    shared_ptr<EveApiDataCharacters> parsedData( new EveApiDataCharacters );
    // do parsing here
    QDomElement root = doc->documentElement();

    if ( root.tagName() != QString( "eveapi" ) )
    {
        emit requestFailed( parserId, QString( "Error parsing the data. Invalid eveapi XML data." ) , QString() );
        return;
    }
    else
    {
        QDomNode firstLevel = root.firstChild();
        while ( !firstLevel.isNull() )
        {
            if ( firstLevel.toElement().tagName() == QString( "currentTime" ) )
            {
                QString dateText = firstLevel.toElement().text();
                QDateTime date = this->apiDateTimeToQDateTime( dateText );
                parsedData->setTimeFetched( date );
            }
            else if ( firstLevel.toElement().tagName() == QString( "result" ) )
            {
                QDomNode secondLevel = firstLevel.firstChild();
                while ( !secondLevel.isNull() )
                {
                    this->parseRowSet( &secondLevel, parsedData );
                    secondLevel = secondLevel.nextSibling();
                }
            }
            else if ( firstLevel.toElement().tagName() == QString( "cachedUntil" ) )
            {
                QString dateText = firstLevel.toElement().text();
                QDateTime date = this->apiDateTimeToQDateTime( dateText );
                parsedData->setCachedUntil( date );
            }
            firstLevel = firstLevel.nextSibling();
        }
    }

    emit parsingComplete( parserId, parsedData );
}

/*!
parse a single character in the xml
*/
void EveApiParserThreadCharacters::parseRowSet( QDomNode* rowset,
        shared_ptr<EveApiDataCharacters>& data )
{
    if ( rowset->toElement().attribute("name") == QString("characters") )
    {
        QDomNode row = rowset->firstChild();
        while ( !row.isNull() )
        {
            QDomElement character = row.toElement();
            QString name = character.attribute( "name" );
            QString corpName = character.attribute( "corporationName" );
            QString charId = character.attribute( "characterID" );
            QString corpId = character.attribute( "corporationID" );
            data->addCharacter( name, corpName, charId, corpId );
            row = row.nextSibling();
        }
    }
}
