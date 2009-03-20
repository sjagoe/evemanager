
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
    QString tempdata = "";
    tempdata.append("<eveapi version=\"2\">");
    tempdata.append(" <currentTime>2008-02-04 13:28:18</currentTime>");
    tempdata.append(" <result>");
    tempdata.append("   <rowset name=\"orders\" key=\"orderID\"");
    tempdata.append("           columns=\"orderID,charID,stationID,volEntered,volRemaining,minVolume,orderState,typeID,range,accountKey,duration,escrow,price,bid,issued\">");
    tempdata.append("     <row orderID=\"639356913\" charID=\"118406849\" stationID=\"60008494\" volEntered=\"25\"");
    tempdata.append("          volRemaining=\"18\" minVolume=\"1\" orderState=\"0\" typeID=\"26082\" range=\"32767\"");
    tempdata.append("          accountKey=\"1000\" duration=\"3\" escrow=\"0.00\" price=\"3398000.00\" bid=\"0\"");
    tempdata.append("          issued=\"2008-02-03 13:54:11\"/>");
    tempdata.append("     <row orderID=\"639477821\" charID=\"118406849\" stationID=\"60004357\" volEntered=\"25\"");
    tempdata.append("          volRemaining=\"24\" minVolume=\"1\" orderState=\"0\" typeID=\"26082\" range=\"32767\"");
    tempdata.append("          accountKey=\"1000\" duration=\"3\" escrow=\"0.00\" price=\"3200000.00\" bid=\"0\"");
    tempdata.append("          issued=\"2008-02-02 16:39:25\"/>");
    tempdata.append("     <row orderID=\"639587440\" charID=\"118406849\" stationID=\"60003760\" volEntered=\"25\"");
    tempdata.append("          volRemaining=\"4\" minVolume=\"1\" orderState=\"0\" typeID=\"26082\" range=\"32767\"");
    tempdata.append("          accountKey=\"1000\" duration=\"1\" escrow=\"0.00\" price=\"3399999.98\" bid=\"1\"");
    tempdata.append("          issued=\"2008-02-03 22:35:54\"/>");
    tempdata.append("   </rowset>");
    tempdata.append(" </result>");
    tempdata.append(" <cachedUntil>2008-02-04 14:28:18</cachedUntil>");
    tempdata.append("</eveapi>");
    shared_ptr<OrdersData> orders = this->_parser.parse(tempdata);

    this->_widget = new OrdersWidget;
    this->_label = "Market Orders";
    this->_mdlSellOrders.reset(new TableModel(orders->getHeader(), orders->getSellOrders()));
    this->_mdlBuyOrders.reset(new TableModel(orders->getHeader(), orders->getBuyOrders()));
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
