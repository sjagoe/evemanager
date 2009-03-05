
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

#ifndef CHARACTERPLUGIN_H
#define CHARACTERPLUGIN_H

#include <QList>
#include <QObject>
#include <QTabWidget>

#include <boost/shared_ptr.hpp>

#include "maininterface.h"

#include "characterplugininterface.h"

using boost::shared_ptr;

class CharacterPlugin : public QObject, MainInterface
{
    Q_OBJECT;
    Q_INTERFACES(MainInterface);
public:
    CharacterPlugin();

    virtual void initialise();

    virtual QWidget* getWidget();

    virtual void setPluginPath(const QStringList& pluginPath);

    virtual void update(QString& id,
                        QString& result,
                        QString& httpResponse,
                        QDateTime& cacheExpireTime,
                        QString& requestType);

private:

    QStringList _pluginPath;

    QTabWidget* _tabWidget;

    QList<shared_ptr<CharacterPluginInterface> > _plugins;

signals:
    void propogateUpdate(QString& result,
                         QString& requestType);
};

#endif // CHARACTERPLUGIN_H
