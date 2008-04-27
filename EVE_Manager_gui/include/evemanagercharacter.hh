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

#ifndef EVEMANAGERCHARACTER_HH_INCLUDED
#define EVEMANAGERCHARACTER_HH_INCLUDED

#include <QWidget>

class QPushButton;
class QGroupBox;
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
    };
};

#endif // EVEMANAGERCHARACTERWIDGET_HH_INCLUDED
