
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

#include "include/characterplugin.h"

#include <QtPlugin>

#include "pluginloader.h"

CharacterPlugin::CharacterPlugin()
{
    this->_tabWidget = new QTabWidget();
}

void CharacterPlugin::initialise()
{
    this->_plugins = loadPlugins<CharacterPluginInterface>(this->_pluginPath);
    foreach(shared_ptr<CharacterPluginInterface> plugin, this->_plugins)
    {
        this->_tabWidget->addTab(plugin->getWidget(), plugin->getLabel());
    }
}

QWidget* CharacterPlugin::getWidget()
{
    return this->_tabWidget;
}

void CharacterPlugin::setPluginPath(const QStringList& pluginPath)
{
    this->_pluginPath = pluginPath;
    this->_pluginPath << "character";
}

void CharacterPlugin::update(QString& result, QString& requestType)
{
    foreach(shared_ptr<CharacterPluginInterface> plugin, this->_plugins)
    {
        plugin->update(result, requestType);
    }
}

Q_EXPORT_PLUGIN2(characterplugin, CharacterPlugin);
