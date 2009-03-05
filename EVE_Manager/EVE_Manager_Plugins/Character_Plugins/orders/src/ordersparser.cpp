
/*
 * Copyright 2009 Simon Jagoe
 *
 * This file is part of EVE_Manager.
 *
 * EVE_Manager is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EVE_Manager is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EVE_Manager.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "include/ordersparser.h"

// Shamelessly copied form EVE_API_Parser

//<eveapi version="2">
//  <currentTime>2008-02-04 13:28:18</currentTime>
//  <result>
//    <rowset name="orders" key="orderID"
//            columns="orderID,charID,stationID,volEntered,volRemaining,minVolume,orderState,typeID,range,accountKey,duration,escrow,price,bid,issued">
//      <row orderID="639356913" charID="118406849" stationID="60008494" volEntered="25"
//           volRemaining="18" minVolume="1" orderState="0" typeID="26082" range="32767"
//           accountKey="1000" duration="3" escrow="0.00" price="3398000.00" bid="0"
//           issued="2008-02-03 13:54:11"/>
//      <row orderID="639477821" charID="118406849" stationID="60004357" volEntered="25"
//           volRemaining="24" minVolume="1" orderState="0" typeID="26082" range="32767"
//           accountKey="1000" duration="3" escrow="0.00" price="3200000.00" bid="0"
//           issued="2008-02-02 16:39:25"/>
//      <row orderID="639587440" charID="118406849" stationID="60003760" volEntered="25"
//           volRemaining="4" minVolume="1" orderState="0" typeID="26082" range="32767"
//           accountKey="1000" duration="1" escrow="0.00" price="3399999.98" bid="0"
//           issued="2008-02-03 22:35:54"/>
//    </rowset>
//  </result>
//  <cachedUntil>2008-02-04 14:28:18</cachedUntil>
//</eveapi>

shared_ptr<OrdersData> OrdersParser::parse(const QString& data)
{
}

bool OrdersParser::runXQuery(
        const QString& queryString, const QString& data, QXmlResultItems& result )
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

QMap<QString, QString> OrdersParser::getRowDataByName(
        const QString& rowsetName, const QString& key, const QString& keyVal,
        const QString& data, const QStringList& columns )
{
    QMap<QString, QString> rowValues;
    QString query = "string(doc($inputDocument)//rowset[@name=\"%1\"]/row[@%2=\"%3\"]/@%4)";
    query = query.arg(rowsetName).arg(key).arg(keyVal);
    foreach(const QString& column, columns)
    {
        QString fullQuery = query.arg(column);
        foreach (const QVariant& value, this->getAtomicValues(fullQuery, data))
        {
            rowValues.insert(column, value.value<QString>());
        }
    }
    return rowValues;
}

QDateTime OrdersParser::getServerTime(const QString& data)
{
    QString query = "string(doc($inputDocument)/eveapi/currentTime)";
    QString tempDate;
    QVariant value = this->getAtomicValue(query, data);
    if (value.isValid())
        tempDate = value.value<QString>();
    QDateTime dateTime = QDateTime::fromString(tempDate, QString("yyyy-MM-dd hh:mm:ss"));
    return dateTime;
}

QList<QVariant> OrdersParser::getAtomicValues( const QString& query, const QString& data )
{
    QList<QVariant> values;
    QXmlResultItems result;
    if (this->runXQuery(query, data, result))
    {
        QXmlItem item(result.next());
        while (!item.isNull())
        {
            if (item.isAtomicValue())
            {
                values << item.toAtomicValue();
            }
            item = result.next();
        }
    }
    return values;
}

// TODO: should this assert the length is one?
QVariant OrdersParser::getAtomicValue( const QString& query, const QString& data )
{
    QList<QVariant> values = this->getAtomicValues(query, data);
    if (values.length() == 0)
        return QVariant();
    return values.takeFirst();
}

QString OrdersParser::runXQuery( const QString& queryString, const QString& data )
{
    QBuffer device;
    device.setData(data.toUtf8());
    device.open(QIODevice::ReadOnly);
    QXmlQuery query;
    query.bindVariable("inputDocument", &device);
    query.setQuery(queryString);
    QBuffer output;
    output.open(QIODevice::WriteOnly);
    QXmlSerializer result(query, &output);
    if (!query.isValid())
        output.close();
        return QString();
    query.evaluateTo(&result);
    output.close();
    return QString(output.data());
}
