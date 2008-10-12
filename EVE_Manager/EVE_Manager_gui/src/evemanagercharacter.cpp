/*
 * Copyright 2008 Simon Jagoe
 *
 * This file is part of EVE Manager.
 *
 * EVE Manager is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EVE Manager is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EVE Manager.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "evemanagercharacter.hh"
#include "evemanagercharactersettings.hh"

#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>

/*!
  Create the character widget
*/
em_gui::EveManagerCharacter::EveManagerCharacter( QWidget* parent ) :
    QWidget( parent )
{
    this->setLayout( this->_layoutWidget() );
}

/*!
  Set up the character widget
*/
QLayout* em_gui::EveManagerCharacter::_layoutWidget()
{
    this->_btnSettings = new QPushButton( tr( "&Settings" ) );

    this->_grpCharacter = new QGroupBox( tr( "Character" ) );
    this->_btnSkillTree = new QPushButton( tr( "Skill &Tree" ) );

    this->_stackDetails = new QStackedWidget;

    em_gui::EveManagerCharacterSettings* emcs = new EveManagerCharacterSettings;
    this->_characterDetails.insert( this->_btnSettings, emcs );
    this->_stackDetails->addWidget( emcs );

    QWidget* nw = new QWidget;
    this->_characterDetails.insert( this->_btnSkillTree, nw );
    this->_stackDetails->addWidget( nw );

    QVBoxLayout* layoutGrpCharacter = new QVBoxLayout;
    layoutGrpCharacter->addWidget( this->_btnSkillTree );
    layoutGrpCharacter->addStretch(1);

    this->_grpCharacter->setLayout( layoutGrpCharacter );

    QVBoxLayout* layoutSelectors = new QVBoxLayout;
    layoutSelectors->addWidget( this->_btnSettings );
    layoutSelectors->addWidget( this->_grpCharacter );
    layoutSelectors->addStretch(2);

    QHBoxLayout* layoutWidget = new QHBoxLayout;
    layoutWidget->addLayout( layoutSelectors );
    layoutWidget->addWidget( this->_stackDetails );

    this->_connect();

    return layoutWidget;
}

/*!
  Connect buttons etc
*/
void em_gui::EveManagerCharacter::_connect()
{
    connect( this->_btnSettings, SIGNAL(clicked()),
             this, SLOT(on_btnSettings_clicked()));
    connect( this->_btnSkillTree, SIGNAL(clicked()),
             this, SLOT(on_btnSkillTree_clicked()));
}

/*!
  Show the Settings pane
*/
void em_gui::EveManagerCharacter::on_btnSettings_clicked()
{
    this->_stackDetails->setCurrentWidget(
        this->_characterDetails.value( this->_btnSettings ) );
}

/*!
  Show the SkillTree pane
*/
void em_gui::EveManagerCharacter::on_btnSkillTree_clicked()
{
    this->_stackDetails->setCurrentWidget(
        this->_characterDetails.value( this->_btnSkillTree ) );
}
