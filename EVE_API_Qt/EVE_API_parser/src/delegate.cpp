
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

#include "delegate.h"

EveApi::Delegate::Delegate( QObject* parent ):
        QObject(parent)
{
}

bool EveApi::Delegate::runXQuery( QString& queryString, QString& data, QXmlResultItems& result )
{
    QBuffer device;
    device.setData(data.toUtf8());
    device.open(QIODevice::ReadOnly);

    QXmlQuery query;
    query.bindVariable("inputDocument", &device);
    query.setQuery(queryString);

    if (!query.isValid())
        return false;
    query.evaluateTo(&result);
    return true;
}

// TODO: This should take a rowset name rather than a path to the row...
QMap<QString, EveApi::DataItem> EveApi::Delegate::getRowData(
        QString& rowsetName, QString& key, QString& keyVal, QString& data, QStringList& columns )
{
    QMap<QString, EveApi::DataItem> rowValues;
    QString query = "string(doc($inputDocument)//rowset[@name=\"%1\"]/row[@%2=\"%3\"]/@%4)";
    query = query.arg(rowsetName).arg(key).arg(keyVal);
    QString column;
    foreach(column, columns)
    {
        QXmlResultItems result;
        QString thisQuery = query.arg(column);
        if (this->runXQuery(thisQuery, data, result))
        {
            QXmlItem item(result.next());
            while (!item.isNull())
            {
                if (item.isAtomicValue())
                {
                    rowValues.insert(column, EveApi::DataItem(item.toAtomicValue().value<QString>()));
                }
                item = result.next();
            }
        }
    }
    return rowValues;
}

QDateTime EveApi::Delegate::getServerTime(QString& data)
{
    QXmlResultItems result;
    QString query = "string(doc($inputDocument)/eveapi/currentTime)";
    QString tempDate;
    if (this->runXQuery(query, data, result))
    {
        QXmlItem item(result.next());
        while (!item.isNull())
        {
            if (item.isAtomicValue())
            {
                tempDate = item.toAtomicValue().value<QString>();
            }
            item = result.next();
        }
    }
    QDateTime dateTime = QDateTime::fromString(tempDate, QString("yyyy-MM-dd hh:mm:ss"));
    return dateTime;
}
