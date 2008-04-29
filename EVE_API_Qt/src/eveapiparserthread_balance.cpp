
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

#include "eveapiparserthread_balance.hh"

#include <QMetaType>
#include <QDomNode>
#include <QDomElement>

#include <QDomDocument>

#include <QMap>

#include <QStringList>

#include "eveapidata_balance.hh"

/*!
Construct the parser
*/
EveApiParserThreadBalance::EveApiParserThreadBalance( QObject* parent ) :
        EveApiParserThread( PDT_ACCOUNTBALANCE, parent )
{
    qRegisterMetaType<shared_ptr<EveApiDataBalance> >( "shared_ptr<EveApiDataBalance>" );
}

/*!
Perform the actual parsing of the data, and emit a signal when done.
The signal must be defined in the subclass
*/
void EveApiParserThreadBalance::doParse( const QString& parserId, const shared_ptr<QDomDocument> doc )
{
    shared_ptr<EveApiDataBalance> parsedData( new EveApiDataBalance );
    // do parsing here
    QDomElement root = doc->documentElement();

    if ( root.tagName() != QString( "eveapi" ) )
    {
        emit requestFailed( parserId, QString("Error parsing the data. Invalid eveapi XML data.") , QString() );
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
parse a "rowset" in the account balance data
*/
void EveApiParserThreadBalance::parseRowSet( QDomNode* rowset,
        shared_ptr<EveApiDataBalance>& data )
{
    if ( rowset->toElement().attribute("name") == QString("accounts") )
    {
        QDomElement rowSetElement = rowset->toElement();
        QString key = rowSetElement.attribute("key");
        QString columns = rowSetElement.attribute("columns");
        QStringList columnsList = columns.split(",");
        QString name = rowSetElement.attribute("name");
        data->setName(name);
        data->setKey(key);
        data->setColumns(columnsList);
        QDomNode row = rowset->firstChild();
        while ( !row.isNull() )
        {
            QDomElement rowElement = row.toElement();
            QString accountKey = rowElement.attribute( "accountKey" );
            QString accountID = rowElement.attribute( "accountID" );
            QString accountBalance = rowElement.attribute( "balance" );
            int key = accountKey.toInt();

            QMap<QString, QString> accountData;
            accountData.insert( QString("accountKey"), accountKey );
            accountData.insert( QString("accountID"), accountID );
            accountData.insert( QString("balance"), accountBalance );

            data->addAccount( key, accountData );

            row = row.nextSibling();
        }
    }
}
