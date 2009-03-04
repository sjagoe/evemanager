#include <QtGui>

#include "include/evemanagerwindow.h"

#include "pluginloader.h"

EveManagerWindow::EveManagerWindow()
{
    QStringList dirs = QStringList("plugins");
    QList<shared_ptr<MainInterface> > plugins = loadPlugins<MainInterface>(dirs);
    if (plugins.length() == 0)
    {
        QMessageBox::information(this, "Error", "Could not load the plugin");
    }
    else
    {
        this->_interface = plugins.at(0);
        this->_interface->setPluginPath(dirs);
        this->_interface->initialise();
        this->setCentralWidget(this->_interface->getWidget());
    }
}
