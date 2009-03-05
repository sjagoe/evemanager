
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

#ifndef ORDERSPLUGIN_H
#define ORDERSPLUGIN_H

#include <QObject>
#include <QString>

#include "characterplugininterface.h"

#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

class OrdersWidget;

class TableModel;

class OrdersPlugin : public QObject, CharacterPluginInterface
{
    Q_OBJECT;
    Q_INTERFACES(CharacterPluginInterface);
public:
    OrdersPlugin();
    virtual QWidget* getWidget();
    virtual const QString& getLabel() const;
    virtual void initialise() {}

    virtual void update(QString& result,
                        QString& requestType) {}

private:
    OrdersWidget* _widget;

    QString _label;

    shared_ptr<TableModel> _mdlSellOrders;
    shared_ptr<TableModel> _mdlBuyOrders;
};

#endif // ORDERSPLUGIN_H
