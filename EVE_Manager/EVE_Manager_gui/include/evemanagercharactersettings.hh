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

#ifndef EVEMANAGERCHARACTERSETTINGS_HH_INCLUDED
#define EVEMANAGERCHARACTERSETTINGS_HH_INCLUDED

#include <QStringList>
#include <QWidget>

class QButtonGroup;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QRadioButton;

namespace em_gui
{
    class EveManagerCharacterSelector;

    class EveManagerCharacterSettings: public QWidget
    {
	Q_OBJECT;
    public:
	/*!
	  Set up the character settings widget
	*/
	EveManagerCharacterSettings( const QString& userID = QString(),
				     const QString& charID = QString(),
				     const QString& apiKey = QString(),
				     bool apiLevel = false,
				     bool corpLevel = false,
				     QWidget* parent = 0 );

    public slots:
	/*!
	  Update the widget
	*/
	void update( const QString& userID,
		     const QString& charID,
		     const QString& apiKey,
		     bool apiLevel,
		     bool corpLevel );

	/*
	  Select a character
	 */
	void selectCharacter( const QStringList &characters );
	
    private:
	//! Label for User ID
	QLabel* _lblUserID;
	//! User ID field
	QLineEdit* _edtUserID;
	//! Label for Character ID
	QLabel* _lblCharacterID;
	//! Character ID field (read only)
	QLineEdit* _edtCharacterID;
	//! Label API Key
	QLabel* _lblApiKey;
	//! API Key field
	QLineEdit* _edtApiKey;
	//! ButtonGroup containing radio buttons to select API functionality
	QButtonGroup* _bgrpApiFunctionality;
	//! Radio Button to select limited API functionality
	QRadioButton* _radApiLimited;
	//! Radio Button to select full API functionality
	QRadioButton* _radApiFull;
	//! Group to store full API settings
	QGroupBox* _grpCorporationFunctionality;
	//! Radio Button to enable Full coprporation setting (requires
	//! Director status)
	QRadioButton* _radCorporationFull;
	//! Radio Button to enable limited Corporation settings (but still
	//! Full character settings (does not need Director status)
	QRadioButton* _radCorporationLimited;
	//! Container for buttons
	QDialogButtonBox* _btnbox;

	em_gui::EveManagerCharacterSelector* _dlgSelector;

	/*!
	  Set up the widget layout
	*/
	QLayout* _setupWidget();
			       
	/*
	  Connect signals and slots
	 */
	void _connectInternals();
			       
    private slots:
	/*!
	  Apply settings
	*/
	void on_btnApply_clicked();

	/*!
	  Reset to stored settings
	*/
	void on_btnReset_clicked();

	/*!
	  A characer has been selected
	*/
	void characterSelected( const QString &character );

    signals:
	/*!
	  Settings have been updated
	*/
	void settingsApplied( const QString &userID,
			      const QString &apiKey );

	/*!
	  Changes cancelled, retrieve (original settings)
	*/
	void settingsCanceled();

	/*
	  Set the character in the model
	*/
	void setCharacter( const QString &userID,
			   const QString &character,
			   const QString &apiKey,
			   const bool &apiLevel,
			   const bool &corpLevel );
	
    };
};

#endif // EVEMANAGERCHARACTERSETTINGS_HH_INCLUDED
