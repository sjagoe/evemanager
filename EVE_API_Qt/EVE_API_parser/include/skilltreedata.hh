
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
  <currentTime>2007-12-22 21:51:40</currentTime>
  <result>
    <rowset name="skillGroups" key="groupID" columns="groupName,groupID">
      <row groupName="Corporation Management" groupID="266">
        <rowset name="skills" key="typeID" columns="typeName,groupID,typeID">
          <row typeName="Anchoring" groupID="266" typeID="11584">
            <description>Skill at Anchoring Deployables. Can not be trained on Trial Accounts.</description>
            <rank>3</rank>
            <rowset name="requiredSkills" key="typeID" columns="typeID,skillLevel" />
            <requiredAttributes>
              <primaryAttribute>memory</primaryAttribute>
              <secondaryAttribute>charisma</secondaryAttribute>
            </requiredAttributes>
            <rowset name="skillBonusCollection" key="bonusType" columns="bonusType,bonusValue">
              <row bonusType="canNotBeTrainedOnTrial" bonusValue="1" />
            </rowset>
          </row>
          <row typeName="CFO Training" groupID="266" typeID="3369">
            <description>Skill at managing corp finances. 5% discount on all fees at non-hostile NPC station if acting as CFO of a corp. </description>
            <rank>3</rank>
            <rowset name="requiredSkills" key="typeID" columns="typeID,skillLevel">
              <row typeID="3363" skillLevel="2" />
              <row typeID="3444" skillLevel="3" />
            </rowset>
            <requiredAttributes>
              <primaryAttribute>memory</primaryAttribute>
              <secondaryAttribute>charisma</secondaryAttribute>
            </requiredAttributes>
            <rowset name="skillBonusCollection" key="bonusType" columns="bonusType,bonusValue" />
          </row>
          <row typeName="Corporation Management" groupID="266" typeID="3363">
            <description>Basic corporation operation. +10 corporation members allowed per level.
 
Notice:  the CEO must update his corporation through the corporation user interface before the skill takes effect</description>
            <rank>1</rank>
            <rowset name="requiredSkills" key="typeID" columns="typeID,skillLevel" />
            <requiredAttributes>
              <primaryAttribute>memory</primaryAttribute>
              <secondaryAttribute>charisma</secondaryAttribute>
            </requiredAttributes>
            <rowset name="skillBonusCollection" key="bonusType" columns="bonusType,bonusValue">
              <row bonusType="corporationMemberBonus" bonusValue="10" />
            </rowset>
          </row>
        </rowset>
      </row>
    </rowset>
  </result>
  <cachedUntil>2007-12-23 21:51:40</cachedUntil>
</eveapi>
 */
