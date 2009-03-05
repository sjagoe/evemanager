
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

#include "include/evemanagerwindow.h"

#include <QMessageBox>

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
        this->setCentralWidget(this->_interface->getWidget());
    }
}
