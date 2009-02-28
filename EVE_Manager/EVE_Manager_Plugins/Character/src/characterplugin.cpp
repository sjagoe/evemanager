#include "include/characterplugin.h"

#include <QtGui>

CharacterPlugin::CharacterPlugin()
{
    this->_tabWidget = new QTabWidget();
    this->_loadPlugins();
    foreach(shared_ptr<CharacterPluginInterface> plugin, this->_plugins)
    {
        this->_tabWidget->addTab(plugin->getWidget(), plugin->getLabel());
    }
}

QWidget* CharacterPlugin::getWidget()
{
    return this->_tabWidget;
}

bool CharacterPlugin::_loadPlugins()
{
    QDir pluginsDir(qApp->applicationDirPath());
    if (!pluginsDir.cd("plugins"))
    {
        return false;
    }
    if (!pluginsDir.cd("character"))
    {
        return false;
    }
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();
        if (plugin) {
            shared_ptr<CharacterPluginInterface> interface(qobject_cast<CharacterPluginInterface *>(plugin));
            if (interface)
                this->_plugins.append(interface);
        }
    }
    return true;
}

Q_EXPORT_PLUGIN2(characterplugin, CharacterPlugin);
