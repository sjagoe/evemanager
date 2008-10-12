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

#include "evemanagercharacterselector.hh"

#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QListWidget>

/*
  Create the widget
*/
em_gui::EveManagerCharacterSelector::EveManagerCharacterSelector(
    QWidget *parent )
    : QWidget( parent )
{
    this->createWidget();
}

/*
  Set the characters in the list
*/
void em_gui::EveManagerCharacterSelector::setCharacters(
    const QStringList &characters )
{
    this->_lstCharacters->addItems( characters );
}

/*!
  Create and lay out the widget
*/
void em_gui::EveManagerCharacterSelector::createWidget()
{
    this->setWindowTitle( tr("Select a Character",
                             "to add to the application") );

    this->_lstCharacters = new QListWidget;
    this->_dlgButtons = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel );

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(this->_lstCharacters);
    layout->addWidget(this->_dlgButtons);
    this->setLayout(layout);
}

/*
  Ok button clicked
*/
void em_gui::EveManagerCharacterSelector::on_dlgButtons_accept()
{
    QString character = this->_lstCharacters->currentItem()->text();
    emit characterSelected( character );
    this->hide();
}

/*
  Cancel button clicked
*/
void em_gui::EveManagerCharacterSelector::on_dlgButtons_cancel()
{
    emit characterCancelled();
    this->hide();
}
