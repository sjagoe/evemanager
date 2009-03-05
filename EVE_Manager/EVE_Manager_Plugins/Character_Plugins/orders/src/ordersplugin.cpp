
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

#include "include/ordersplugin.h"

#include <QtPlugin>
#include <QList>
#include <QStringList>

#include "orderswidget.h"
#include "tablemodel.h"

OrdersPlugin::OrdersPlugin()
{
    this->_widget = new OrdersWidget;
    this->_label = "Market Orders";
    int columns = 6;
    int rows = 100;
    QStringList header;
    QString base = "Column %1";
    for (int i = 1; i <= columns; ++i)
    {
        header << base.arg(i);
    }
    QList<QStringList> data;
    base = "sell: row %1 col %2";
    for (int i = 1; i <= rows; ++i)
    {
        QStringList item;
        for (int j = 1; j <= columns; ++j)
        {
            item << base.arg(i).arg(j);
        }
        data.append(item);
    }
    this->_mdlSellOrders.reset(new TableModel(header, data));
    data.clear();
    base = "buy: row %1 col %2";
    for (int i = 1; i <= rows; ++i)
    {
        QStringList item;
        for (int j = 1; j <= columns; ++j)
        {
            item << base.arg(i).arg(j);
        }
        data.append(item);
    }
    this->_mdlBuyOrders.reset(new TableModel(header, data));
    this->_widget->setModels(this->_mdlSellOrders, this->_mdlBuyOrders);
}

QWidget* OrdersPlugin::getWidget()
{
    return this->_widget;
}

const QString& OrdersPlugin::getLabel() const
{
    return this->_label;
}

Q_EXPORT_PLUGIN2(ordersplugin, OrdersPlugin);
