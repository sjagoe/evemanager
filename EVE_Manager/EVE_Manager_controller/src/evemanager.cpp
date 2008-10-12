/*
 * Copyright 2008 Simon Jagoe
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

#include "evemanager.hh"
#include "../EVE_Manager_gui/include/evemanagerwindow.hh"

#include <QHBoxLayout>

/*!
  Create model and gui
*/
em_controller::EveManager::EveManager( QObject* parent ) :
    QObject( parent )
{
    this->_eveManagerGui = new em_gui::EveManagerWindow;
    connect( this->_eveManagerGui, SIGNAL(exit()), this, SIGNAL(exit()));
    this->_eveManagerGui->show();
}
