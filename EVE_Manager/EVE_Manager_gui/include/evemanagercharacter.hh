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

#ifndef EVEMANAGERCHARACTER_HH_INCLUDED
#define EVEMANAGERCHARACTER_HH_INCLUDED

#include <QMap>
#include <QWidget>

class QPushButton;
class QGroupBox;
class QLayout;
class QStackedWidget;

namespace em_gui
{
    class EveManagerCharacter: public QWidget
    {
        Q_OBJECT
        public:
            /*!
            Create the character widget
            */
            EveManagerCharacter( QWidget* parent = 0 );

        private:
            //! Button to access the "Settings" pane
            QPushButton* _btnSettings;

            //! Group box containing buttons related to character stuff
            QGroupBox* _grpCharacter;
            //! Button to select the character's skill tree
            QPushButton* _btnSkillTree;

            //! stack containing all the detailed attributes for a character
            QStackedWidget* _stackDetails;

            //! map buttons to a widget to display in the stack
            QMap<QPushButton*, QWidget*> _characterDetails;

            /*!
            Set up the character widget
            */
            QLayout* _layoutWidget();

            /*!
            Connect buttons etc
            */
            void _connect();

        private slots:
            /*!
            Show the Settings pane
            */
            void on_btnSettings_clicked();

            /*!
            Show the SkillTree pane
            */
            void on_btnSkillTree_clicked();
    };
};

#endif // EVEMANAGERCHARACTERWIDGET_HH_INCLUDED
