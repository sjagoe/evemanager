
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

#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#include <QtCore>
#include <QDir>
#include <QList>
#include <QString>
#include <QStringList>

#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

template<class T>
QList<shared_ptr<T> > loadPlugins(const QStringList pluginsDirList)
{
    QList<shared_ptr<T> > plugins;
    QDir pluginsDir(qApp->applicationDirPath());
    foreach (const QString& dir, pluginsDirList)
    {
        if (!pluginsDir.cd(dir))
        {
            return plugins;
        }
    }
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject* plugin = pluginLoader.instance();
        if (plugin) {
            shared_ptr<T> T_ptr = shared_ptr<T>(qobject_cast<T*>(plugin));
            T_ptr->setPluginPath(pluginsDirList);
            T_ptr->initialise();
            plugins.append(T_ptr);
        }
    }
    return plugins;
}


#endif // PLUGINLOADER_H
