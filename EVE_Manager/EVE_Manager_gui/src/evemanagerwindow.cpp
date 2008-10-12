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

#include "evemanagerwindow.hh"

#include "evemanagercharacter.hh"

//#include <QHBoxLayout>
#include <QMenuBar>
#include <QPushButton>
#include <QTabWidget>

/*!
  Create and populate the window.
*/
em_gui::EveManagerWindow::EveManagerWindow( QWidget* parent ) :
    QMainWindow( parent )
{
    QMenu* fileMenu = this->menuBar()->addMenu( tr( "&File" ) );
    QAction* quit =
        fileMenu->addAction( tr( "&Quit", "Quit the application" ),
                             this, SIGNAL( exit() ) );
    quit->setShortcut( tr( "Ctrl+Q", "Quit the application" ) );

    this->_characters = new QTabWidget;

    EveManagerCharacter* chara = new EveManagerCharacter;
    this->_characters->addTab( chara, tr("Character") );

    this->setCentralWidget( this->_characters );
}

