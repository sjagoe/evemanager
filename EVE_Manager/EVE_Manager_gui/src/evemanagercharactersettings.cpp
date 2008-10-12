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

#include "evemanagercharactersettings.hh"
#include "evemanagercharacterselector.hh"

#include <QButtonGroup>
#include <QDialogButtonBox>
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
    QWidget* parent )
    : QWidget( parent ),
      _apiLevel(false),
      _corpLevel(false)
{
    this->setLayout( this->_setupWidget() );
    this->update( userID, charID, apiKey, apiLevel, corpLevel );
}

/*!
  Update the widget
*/
void em_gui::EveManagerCharacterSettings::update(
    const QString& userID,
    const QString& charID,
    const QString& apiKey,
    bool apiLevel,
    bool corpLevel )
{
    this->_edtUserID->setText(userID);
    this->_edtCharacterID->setText(charID);
    this->_edtApiKey->setText( apiKey );

    // set checked buttons
    if ( corpLevel )
    {
        this->_radCorporationFull->click();
    }
    else
    {
        this->_radCorporationLimited->click();
    }
    if ( apiLevel )
    {
        this->_radApiFull->click();
        this->_grpCorporationFunctionality->setEnabled( true );
    }
    else
    {
        this->_radApiLimited->click();
        this->_grpCorporationFunctionality->setEnabled( false );
    }
}

/*
  Select a character
*/
void em_gui::EveManagerCharacterSettings::selectCharacter(
    const QStringList &characters )
{
    this->_dlgSelector->setCharacters( characters );
    this->_dlgSelector->show();
}

/*!
  Set up the widget layout
*/
QLayout* em_gui::EveManagerCharacterSettings::_setupWidget()
{
    // Label for User ID
    this->_lblUserID = new QLabel( tr( "User ID" ) );
    // User ID field
    this->_edtUserID = new QLineEdit();
    // Label for Character ID
    this->_lblCharacterID = new QLabel( tr( "Character ID" ) );
    // Character ID field (read only)
    this->_edtCharacterID = new QLineEdit();
    this->_edtCharacterID->setReadOnly( true );
    // Label API Key
    this->_lblApiKey = new QLabel( tr( "API Key" ) );
    // API Key field
    this->_edtApiKey = new QLineEdit();
    // Radio Button to select limited API functionality
    this->_radApiLimited = new QRadioButton(
        tr( "Limited API Functionality" ) );
    // Radio Button to select full API functionality
    this->_radApiFull = new QRadioButton( tr( "Full API Functionality" ) );
    // ButtonGroup containing radio buttons to select API functionality
    this->_bgrpApiFunctionality = new QButtonGroup;
    this->_bgrpApiFunctionality->addButton( this->_radApiLimited );
    this->_bgrpApiFunctionality->addButton( this->_radApiFull );
    // Group to store full API settings
    this->_grpCorporationFunctionality = new QGroupBox(
        tr( "Corporation Functionality Level" ) );
    // Radio Button to enable limited Corporation settings (but still
    // Full character settings (does not need Director status)
    this->_radCorporationLimited = new QRadioButton(
        tr( "Limited Corporation Access" ) );
    // Radio Button to enable Full coprporation setting (requires
    // Director status)
    this->_radCorporationFull = new QRadioButton(
        tr( "Full Corporation Access (requires Director access)" ) );
    // ButtonGroup containing radio buttons to select Corp Access Level
    this->_bgrpCorporationFunctionality = new QButtonGroup;
    this->_bgrpCorporationFunctionality->addButton( this->_radCorporationLimited );
    this->_bgrpCorporationFunctionality->addButton( this->_radCorporationFull );
    this->_btnbox = new QDialogButtonBox(
        QDialogButtonBox::Apply | QDialogButtonBox::Reset );

    // layouts

    QHBoxLayout* layoutApiFunctionality = new QHBoxLayout;
    layoutApiFunctionality->addWidget( this->_radApiLimited );
    layoutApiFunctionality->addWidget( this->_radApiFull );

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
    layoutGrid->addLayout( layoutApiFunctionality, 4, 0, 1, 2 );
    layoutGrid->addWidget( this->_grpCorporationFunctionality, 5, 0, 1, 2 );
    layoutGrid->addWidget( this->_btnbox, 6, 0, 1, 2 );

    QVBoxLayout* layoutWidget = new QVBoxLayout;
    layoutWidget->addLayout( layoutGrid );
    layoutWidget->addStretch();

    this->_dlgSelector = new em_gui::EveManagerCharacterSelector();
    
    return layoutWidget;
}

/*
  Connect signals and slots
*/
void em_gui::EveManagerCharacterSettings::_connectInternals()
{
    connect( this->_btnbox, SIGNAL( accepted() ),
             this, SLOT( on_btnApply_clicked() ) );
    connect( this->_btnbox, SIGNAL( rejected() ),
             this, SLOT( on_btnReset_clicked() ) );
    connect( this->_dlgSelector, SIGNAL( characterSelected( QString ) ),
             this, SLOT( characterSelected( QString ) ) );
    connect( this->_dlgSelector, SIGNAL( characterCancelled() ),
             this, SIGNAL( settingsCanceled() ) );
}


/*!
  Apply settings
*/
void em_gui::EveManagerCharacterSettings::on_btnApply_clicked()
{
    emit settingsApplied( this->_edtUserID->text(),
                          this->_edtApiKey->text());
}

/*!
  Reset to stored settings
*/
void em_gui::EveManagerCharacterSettings::on_btnReset_clicked()
{
    emit settingsCanceled();
}

/*!
  A characer has been selected
*/
void em_gui::EveManagerCharacterSettings::characterSelected(
    QString character )
{
    emit setCharacter( this->_edtUserID->text(),
                       character,
                       this->_edtApiKey->text(),
                       this->_apiLevel,
                       this->_corpLevel);
}

/*!
  Set the internal apiLevel value
*/
void em_gui::EveManagerCharacterSettings::on_radApiLimited_clicked()
{
    this->_apiLevel = false;
}

/*!
  Set the internal apiLevel value
*/
void em_gui::EveManagerCharacterSettings::on_radApiFull_clicked()
{
    this->_apiLevel = true;
}

/*!
  Set the internal corpLevel value
*/
void em_gui::EveManagerCharacterSettings::on_radCorpLimited_clicked()
{
    this->_corpLevel = false;
}

/*!
  Set the internal corpLevel value
*/
void em_gui::EveManagerCharacterSettings::on_radCorpFull_clicked()
{
    this->_corpLevel = true;
}
