
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

#include "charactersparser.h"

#include <QBuffer>
#include <QByteArray>
#include <QChar>
#include <QStringList>

EveApi::CharactersParser::CharactersParser( QObject* parent ):
        Delegate(parent)
{
}

void EveApi::CharactersParser::parse( QString& id, QString& data,
                                      QString& httpResponse,
                                      QDateTime& cacheExpireTime )
{
    QString name = this->getRowsetAttribute(data, "name");
    QString key = this->getRowsetAttribute(data, "key");
    QStringList columns = this->getRowsetAttribute(data, "columns").split(QChar(','));

    EveApi::Rowset<void*>* rowset = new EveApi::Rowset<void*>(name, key, columns);

    QStringList characters;
    characters = this->getCharacterIds(data, key);
    QMap<QString, EveApi::DataItem> rowValues;

    QString keyVal;
    foreach(keyVal, characters)
    {
        rowValues = this->getRowData(name, key, keyVal, data, columns);
        rowset->addRow(rowValues);
    }

    int version = this->getApiVersion(data);
    QDateTime currentTime = this->getServerTime(data);
    QSharedPointer<EveApi::CharactersData> charactersData( new EveApi::CharactersData(
            version, currentTime, cacheExpireTime, rowset) );
    emit this->requestComplete(id, charactersData, httpResponse, cacheExpireTime);
}

QString EveApi::CharactersParser::getRowsetAttribute(QString& data, const char* attribute)
{
    QString value;
    QString query = "string(doc($inputDocument)/eveapi/result/rowset/@%1)";
    query = query.arg(attribute);

    QXmlResultItems result;
    if (this->runXQuery(query, data, result))
    {
        QXmlItem item(result.next());
        value = item.toAtomicValue().value<QString>();
    }

    return value;
}

QStringList EveApi::CharactersParser::getCharacterIds(QString& data, QString& key)
{
    QXmlResultItems result;
    QString query = "for $i in doc($inputDocument)/eveapi/result/rowset/row/@%1 return string($i)";
    query = query.arg(key);

    QStringList characters;
    if (this->runXQuery(query, data, result))
    {
        QXmlItem item(result.next());
        while (!item.isNull())
        {
            if (item.isAtomicValue())
            {
                characters << item.toAtomicValue().value<QString>();
            }
            item = result.next();
        }
    }
    return characters;
}

int EveApi::CharactersParser::getApiVersion(QString& data)
{
    QXmlResultItems result;
    QString query = "string(doc($inputDocument)/eveapi/@version)";

    int version;
    if (this->runXQuery(query, data, result))
    {
        QXmlItem item(result.next());
        while (!item.isNull())
        {
            if (item.isAtomicValue())
            {
                version = item.toAtomicValue().value<int>();
            }
            item = result.next();
        }
    }
    return version;
}
