
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
    public:
        AttributeEnhancers();
        AttributeEnhancers(
            QPair<QString, int> intelligence, QPair<QString, int> memory,
            QPair<QString, int> charisma, QPair<QString, int> perception,
            QPair<QString, int> willpower);

        const QPair<QString, int>& get_intelligence() const;
        const QPair<QString, int>& get_memory() const;
        const QPair<QString, int>& get_charisma() const;
        const QPair<QString, int>& get_perception() const;
        const QPair<QString, int>& get_willpower() const;

        const int& get_intelligenceValue() const;
        const int& get_memoryValue() const;
        const int& get_charismaValue() const;
        const int& get_perceptionValue() const;
        const int& get_willpowerValue() const;

        const QString& get_intelligenceName() const;
        const QString& get_memoryName() const;
        const QString& get_charismaName() const;
        const QString& get_perceptionName() const;
        const QString& get_willpowerName() const;

        void set_intelligence(const QPair<QString, int>& intelligence);
        void set_memory(const QPair<QString, int>& memory);
        void set_charisma(const QPair<QString, int>& charisma);
        void set_perception(const QPair<QString, int>& perception);
        void set_willpower(const QPair<QString, int>& willpower);

    private:
        QPair<QString, int> _intelligence;
        QPair<QString, int> _memory;
        QPair<QString, int> _charisma;
        QPair<QString, int> _perception;
        QPair<QString, int> _willpower;
    };

    class Attributes
    {
    public:
        Attributes();
        Attributes(int intelligence, int memory, int charisma, int perception,
                   int willpower);

        const int& get_intelligence() const;
        const int& get_memory() const;
        const int& get_charisma() const;
        const int& get_perception() const;
        const int& get_willpower() const;
    private:
        int _intelligence;
        int _memory;
        int _charisma;
        int _perception;
        int _willpower;
    };

    class CharacterSheetData
    {
    public:
        CharacterSheetData();

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
//        RowSet _skills;
//        RowSet _corporationRoles;
//        RowSet _corporationRolesAtHQ;
//        RowSet _corporationRolesAtBase;
//        RowSet _corporationRolesAtOther;
//        RowSet _corporationTitles;
    };
};


#endif
