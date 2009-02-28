#include <QtGui>

#include "include/evemanagerwindow.h"

EveManagerWindow::EveManagerWindow()
{
    if (!this->_loadPlugin())
    {
        QMessageBox::information(this, "Error", "Could not load the plugin");
    }
    else
    {
        this->setCentralWidget(this->_interface->getWidget());
    }
}

bool EveManagerWindow::_loadPlugin()
{
    QDir pluginsDir(qApp->applicationDirPath());
    if (!pluginsDir.cd("plugins"))
    {
        return false;
    }
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();
        if (plugin) {
            this->_interface.reset(qobject_cast<MainInterface *>(plugin));
            if (this->_interface)
                return true;
        }
    }
    return false;
}
