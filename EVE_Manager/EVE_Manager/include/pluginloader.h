#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#include <QtCore>
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
            plugins.append(shared_ptr<T>(qobject_cast<T*>(plugin)));
        }
    }
    return plugins;
}


#endif // PLUGINLOADER_H
