
/*
 * Copyright 2007-2008 Simon Jagoe
 *
 * This file is part of EVE_API_Qt.
 *
 * EVE_API_Qt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EVE_API_Qt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EVE_API_Qt.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _EVEAPI_CHARACTERSHEET_HH_
#define _EVEAPI_CHARACTERSHEET_HH_

#include <QPair>
#include <QString>

#include "abstracteveapidata.hh"

namespace EveApi
{
    class AttributeEnhancers
    {
    private:
	QPair<QString, int> _intelligence;
	QPair<QString, int> _memory;
	QPair<QString, int> _charisma;
	QPair<QString, int> _perception;
	QPair<QString, int> _willpower;
    };

    class Attributes
    {
    private:
	int _intelligence;
	int _memory;
	int _charisma;
	int _perception;
	int _willpower;
    };

    class CharacterSheetData
    {
    private:
	DataItem _characterID;
	DataItem _name;
	DataItem _bloodline;
	DataItem _gender;
	DataItem _corporationName;
	DataItem _corporationID;
	DataItem _cloneName;
	DataItem _cloneSkillPoints;
	DataItem _balance;
	AttributeEnhancers _attributeEnhancers;
	Attributes _attributes;
	RowSet _skills;
	RowSet _corporationRoles;
	RowSet _corporationRolesAtHQ;
	RowSet _corporationRolesAtBase;
	RowSet _corporationRolesAtOther;
	RowSet _corporationTitles;
    };
};


#endif
