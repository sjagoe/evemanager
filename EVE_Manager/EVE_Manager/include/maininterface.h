
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

#ifndef MAININTERFACE_H
#define MAININTERFACE_H

#include <QDateTime>
#include <QString>

class QWidget;

class MainInterface
{
public:
    virtual ~MainInterface() {}
    virtual void initialise() = 0;
    virtual QWidget* getWidget() = 0;
    virtual void setPluginPath(const QStringList& pluginPath) {}

    virtual void update(QString& id,
                        QString& result,
                        QString& httpResponse,
                        QDateTime& cacheExpireTime,
                        QString& requestType) {}
};

Q_DECLARE_INTERFACE(MainInterface, "com.EveManager.Plugin.MainInterface/0.1");

#endif // MAININTERFACE_H
