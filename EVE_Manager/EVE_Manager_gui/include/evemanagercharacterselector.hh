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

#ifndef __EVEMANAGERCHARACTERSELECTOR_HH__
#define __EVEMANAGERCHARACTERSELECTOR_HH__

#include <QStringList>
#include <QWidget>

class QListWidget;
class QDialogButtonBox;

namespace em_gui
{
    class EveManagerCharacterSelector: public QWidget
    {
	Q_OBJECT;
    public:
	/*
	  Create the widget
	 */
	EveManagerCharacterSelector(QWidget *parent = 0 );

    public slots:
	/*
	  Set the characters in the list
	*/
	void setCharacters( const QStringList &characters );

    private:
	//! Listbox displaying characters on the account
	QListWidget *_lstCharacters;
	//! Buttons to select a character or cancel
	QDialogButtonBox *_dlgButtons;

	/*!
	  Create and lay out the widget
	 */
	void createWidget();

	/*
	  Ok button clicked
	 */
	void on_dlgButtons_accept();

	/*
	  Cancel button clicked
	 */
	void on_dlgButtons_cancel();
	
    signals:
	/*
	  A character has been selected - notify the application
	 */
	void characterSelected( QString character );

	/*
	  Operation cancelled
	 */
	void characterCancelled();
	
    };
};


#endif
