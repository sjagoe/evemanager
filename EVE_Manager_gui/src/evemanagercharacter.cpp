/*
 * Copyright 2008 Simon Jagoe
 *
 * This file is part of <<<<>>>>.
 *
 * <<<<>>>> is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * <<<<>>>> is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with <<<<>>>>.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "evemanagercharacter.hh"

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
    this->_btnSettings = new QPushButton( tr( "&Settings" ) );

    this->_grpCharacter = new QGroupBox( tr( "Character" ) );
    this->_btnSkillTree = new QPushButton( tr( "Skill &Tree" ) );

    this->_stackDetails = new QStackedWidget;

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

    this->setLayout( layoutWidget );
}
