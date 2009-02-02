
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

/*
<?xml version='1.0' encoding='UTF-8'?>
<eveapi version="2">
  <currentTime>2007-06-18 22:49:01</currentTime>
  <result>
    <characterID>150337897</characterID>
    <name>corpslave</name>
    <race>Minmatar</race>
    <bloodLine>Brutor</bloodLine>
    <gender>Female</gender>
    <corporationName>corpexport Corp</corporationName>
    <corporationID>150337746</corporationID>
    <cloneName>Clone Grade Pi</cloneName>
    <cloneSkillPoints>54600000</cloneSkillPoints>
    <balance>190210393.87</balance>
    <attributeEnhancers>
      <intelligenceBonus>
        <augmentatorName>Snake Delta</augmentatorName>
        <augmentatorValue>3</augmentatorValue>
      </intelligenceBonus>
      <memoryBonus>
        <augmentatorName>Halo Beta</augmentatorName>
        <augmentatorValue>3</augmentatorValue>
      </memoryBonus>
    </attributeEnhancers>
    <attributes>
      <intelligence>6</intelligence>
      <memory>4</memory>
      <charisma>7</charisma>
      <perception>12</perception>
      <willpower>10</willpower>
    </attributes>
    <rowset name="skills" key="typeID">
      <row typeID="3431" skillpoints="8000" level="3"/>
      <row typeID="3413" skillpoints="8000" level="3"/>
      <row typeID="21059" skillpoints="500" level="1"/>
      <row typeID="3416" skillpoints="8000" level="3"/>
      <row typeID="3445" skillpoints="277578" unpublished="1"/>
    </rowset>
    <rowset name="certificates" key="certificateID" columns="certificateID">
      <row certificateID="1"/>
      <row certificateID="5"/>
      <row certificateID="19"/>
      <row certificateID="239"/>
      <row certificateID="282"/>
      <row certificateID="32"/>
      <row certificateID="258"/>
    </rowset>
    <rowset name="corporationRoles" key="roleID" columns="roleID,roleName">
      <row roleID="1" roleName="roleDirector" />
    </rowset>
    <rowset name="corporationRolesAtHQ" key="roleID" columns="roleID,roleName">
      <row roleID="1" roleName="roleDirector" />
    </rowset>
    <rowset name="corporationRolesAtBase" key="roleID" columns="roleID,roleName">
      <row roleID="1" roleName="roleDirector" />
    </rowset>
    <rowset name="corporationRolesAtOther" key="roleID" columns="roleID,roleName">
      <row roleID="1" roleName="roleDirector" />
    </rowset>
    <rowset name="corporationTitles" key="titleID" columns="titleID,titleName">
      <row titleID="1" titleName="Member" />
    </rowset>
  </result>
  <cachedUntil>2007-06-18 23:49:01</cachedUntil>
</eveapi>
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
        AttributeEnhancers(
            QPair<QString, int> intelligence, QPair<QString, int> memory,
            QPair<QString, int> charisma, QPair<QString, int> perception,
            QPair<QString, int> willpower);

        const QPair<QString, int>& intelligence() const;
        const QPair<QString, int>& memory() const;
        const QPair<QString, int>& charisma() const;
        const QPair<QString, int>& perception() const;
        const QPair<QString, int>& willpower() const;

        const int& intelligenceValue() const;
        const int& memoryValue() const;
        const int& charismaValue() const;
        const int& perceptionValue() const;
        const int& willpowerValue() const;

        const QString& intelligenceName() const;
        const QString& memoryName() const;
        const QString& charismaName() const;
        const QString& perceptionName() const;
        const QString& willpowerName() const;

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
        Attributes(int intelligence, int memory, int charisma, int perception,
                   int willpower);

        const int& intelligence() const;
        const int& memory() const;
        const int& charisma() const;
        const int& perception() const;
        const int& willpower() const;
    private:
        int _intelligence;
        int _memory;
        int _charisma;
        int _perception;
        int _willpower;
    };

    class CharacterSheetData: public AbstractData
    {
    public:
        /*
          Create a CharacterSheetData instance representing a charactar at a particular point in time.
          */
        CharacterSheetData( const int& version,
                            const QDateTime& currentTime,
                            const QDateTime& cachedUntil,
                            QString& characterID,
                            QString& name,
                            QString& bloodline,
                            QString& gender,
                            QString& corporationName,
                            QString& corporationID,
                            QString& cloneName,
                            QString& cloneSkillPoints,
                            QString& balance,
                            shared_ptr<AttributeEnhancers>& attributeEnhancers,
                            shared_ptr<Attributes>& baseAttributes );

        /*
          Get the character's ID
          */
        const QString& characterID() const;

        /*
          Get the character's name
          */
        const QString& name() const;

        /*
          Get the character's bloodline
          */
        const QString& bloodline() const;

        /*
          Get the character's gender
          */
        const QString& gender() const;

        /*
          Get the name of the character's corporation
          */
        const QString& corporationName() const;

        /*
          Get the ID of the character's corporation
          */
        const QString& corporationID() const;

        /*
          Get the name of the character's clone type
          */
        const QString& cloneName() const;

        /*
          Get the number of skill points the clone can carry
          */
        const QString& cloneSkillPoints() const;

        /*
          Get the character's wallet balance
          */
        const QString& balance() const;

        /*
          Get access to the character's attribute enhancers
          */
        const shared_ptr<AttributeEnhancers>& attributeEnhancers() const;

        /*
          Get access to the character's base attributes (i.e. no enhancers or skills)
          */
        const shared_ptr<Attributes>& baseAttributes() const;

        /*
          Get access to the character's attributes with enhancers and skills
          */
        const shared_ptr<Attributes>& attributes() const;

    private:
        QString _characterID;
        QString _name;
        QString _bloodline;
        QString _gender;
        QString _corporationName;
        QString _corporationID;
        QString _cloneName;
        QString _cloneSkillPoints;
        QString _balance;
        shared_ptr<AttributeEnhancers> _attributeEnhancers;
        shared_ptr<Attributes> _baseAttributes;
        shared_ptr<Attributes> _attributes;
        shared_ptr<Rowset<void*> > _skills;
        shared_ptr<Rowset<void*> > _certificates;
        shared_ptr<Rowset<void*> > _corporationRoles;
        shared_ptr<Rowset<void*> > _corporationRolesAtHQ;
        shared_ptr<Rowset<void*> > _corporationRolesAtBase;
        shared_ptr<Rowset<void*> > _corporationRolesAtOther;
        shared_ptr<Rowset<void*> > _corporationTitles;
    };
}


#endif
