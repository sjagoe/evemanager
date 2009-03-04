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

Q_EXPORT_PLUGIN2(characterplugin, CharacterPlugin);
