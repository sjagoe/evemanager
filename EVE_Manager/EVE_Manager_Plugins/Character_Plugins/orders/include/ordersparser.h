
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

#ifndef ORDERSPARSER_H
#define ORDERSPARSER_H

// Shamelessly copied form EVE_API_Parser

#include <QtXmlPatterns>

#include <QList>
#include <QMap>
#include <QString>
#include <QStringList>

#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

class OrdersData
{
public:
    OrdersData();

    OrdersData(const QStringList& header);

    void addRow(const QStringList& order);

    const QList<QStringList>& getSellOrders() const;

    const QList<QStringList>& getBuyOrders() const;

    const QStringList& getHeader() const;

private:
    QStringList _header;
    QList<QStringList> _sellOrders;
    QList<QStringList> _buyOrders;
    int _bidIndex;
    int _stateIndex;
//    int _accountIndex;
};

class OrdersParser
{
public:
    OrdersParser() {}

    shared_ptr<OrdersData> parse(const QString& data);

protected:
    /*
          Run an XQuery against some XML in a string.
     */
    bool runXQuery( const QString& query, const QString& data, QXmlResultItems& result );
    bool runXQuery( const QString& query, const QString& data, QStringList& result );
    bool runXQuery( const QString& query, const QString& data, QString& result );

    QList<QVariant> getAtomicValues( const QString& query, const QString& data );

    QVariant getAtomicValue( const QString& query, const QString& data );

    QDateTime getServerTime(const QString& data);
};

#endif // ORDERSPARSER_H
