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

#include "evemanagercharactersettings.hh"

#include <QButtonGroup>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QRadioButton>
#include <QVBoxLayout>

/*!
Set up the character settings widget
*/
em_gui::EveManagerCharacterSettings::EveManagerCharacterSettings(
    const QString& userID,
    const QString& charID,
    const QString& apiKey,
    bool apiLevel,
    bool corpLevel,
    QWidget* parent ) :
        QWidget( parent )
{
    this->setLayout(
        this->_setupWidget( userID, charID, apiKey, apiLevel, corpLevel ) );
}

/*!
Set up the widget layout
*/
QLayout* em_gui::EveManagerCharacterSettings::_setupWidget(
    const QString& userID,
    const QString& charID,
    const QString& apiKey,
    bool apiLevel,
    bool corpLevel )
{
    // Group to contain all API settings
    //this->_grpApiSettings = new QGroupBox( tr( "Character's API Settings" ) );
    // Label for User ID
    this->_lblUserID = new QLabel( tr( "User ID" ) );
    // User ID field
    this->_edtUserID = new QLineEdit( userID );
    // Label for Character ID
    this->_lblCharacterID = new QLabel( tr( "Character ID" ) );
    // Character ID field (read only)
    this->_edtCharacterID = new QLineEdit( charID );
    this->_edtCharacterID->setReadOnly( true );
    // Label API Key
    this->_lblApiKey = new QLabel( tr( "API Key" ) );
    // API Key field
    this->_edtApiKey = new QLineEdit( apiKey );
    // ButtonGroup containing radio buttons to select API functionality
    this->_bgrpApiFunctionality = new QButtonGroup;
    // Radio Button to select limited API functionality
    this->_radApiLimited = new QRadioButton(
        tr( "Limited API Functionality" ) );
    // Radio Button to select full API functionality
    this->_radApiFull = new QRadioButton( tr( "Full API Functionality" ) );
    // Group to store full API settings
    this->_grpCorporationFunctionality = new QGroupBox(
        tr( "Corporation Functionality Level" ) );
    // Radio Button to enable Full coprporation setting (requires
    // Director status)
    this->_radCorporationFull = new QRadioButton(
        tr( "Full Corporation Access (requires Director access)" ) );
    // Radio Button to enable limited Corporation settings (but still
    // Full character settings (does not need Director status)
    this->_radCorporationLimited = new QRadioButton(
        tr( "Limited Corporation Access" ) );

    // layouts

    QHBoxLayout* layoutApiFunctionality = new QHBoxLayout;
    layoutApiFunctionality->addWidget( this->_radApiLimited );
    layoutApiFunctionality->addWidget( this->_radApiFull );
//    this->_bgrpApiFunctionality->setLayout( layoutApiFunctionality );

//    this->_bgrpApiFunctionality->addButton( this->_radApiLimited );
//    this->_bgrpApiFunctionality->addButton( this->_radApiFull );

    QHBoxLayout* layoutCorpFunctionality = new QHBoxLayout;
    layoutCorpFunctionality->addWidget( this->_radCorporationLimited );
    layoutCorpFunctionality->addWidget( this->_radCorporationFull );
    this->_grpCorporationFunctionality->setLayout( layoutCorpFunctionality );

    QGridLayout* layoutGrid = new QGridLayout;
    layoutGrid->addWidget( this->_lblUserID, 0, 0 );
    layoutGrid->addWidget( this->_edtUserID, 1, 0 );
    layoutGrid->addWidget( this->_lblCharacterID, 0, 1 );
    layoutGrid->addWidget( this->_edtCharacterID, 1, 1 );
    layoutGrid->addWidget( this->_lblApiKey, 2, 0, 1, 2 );
    layoutGrid->addWidget( this->_edtApiKey, 3, 0, 1, 2 );
    //layoutGrid->addWidget( this->_bgrpApiFunctionality, 4, 0, 1, 2 );
    layoutGrid->addLayout( layoutApiFunctionality, 4, 0, 1, 2 );
    layoutGrid->addWidget( this->_grpCorporationFunctionality, 5, 0, 1, 2 );

    // set checked buttons
    if (corpLevel)
    {
        this->_radCorporationFull->click();
    }
    else
    {
        this->_radCorporationLimited->click();
    }
    if (apiLevel)
    {
        this->_radApiFull->click();
        this->_grpCorporationFunctionality->setEnabled(true);
    }
    else
    {
        this->_radApiLimited->click();
        this->_grpCorporationFunctionality->setEnabled(false);
    }

    QVBoxLayout* layoutWidget = new QVBoxLayout;
    layoutWidget->addLayout(layoutGrid);
    layoutWidget->addStretch();

    return layoutWidget;
}
