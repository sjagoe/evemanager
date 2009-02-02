
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

#include "charactersheetdata.h"

EveApi::AttributeEnhancers::AttributeEnhancers(
    QPair<QString, int> intelligence, QPair<QString, int> memory,
    QPair<QString, int> charisma, QPair<QString, int> perception,
    QPair<QString, int> willpower)
{
    this->_intelligence = intelligence;
    this->_memory = memory;
    this->_charisma = charisma;
    this->_perception = perception;
    this->_willpower = willpower;
}


const QPair<QString, int>& EveApi::AttributeEnhancers::intelligence() const
{
    return this->_intelligence;
}

const QPair<QString, int>& EveApi::AttributeEnhancers::memory() const
{
    return this->_memory;
}

const QPair<QString, int>& EveApi::AttributeEnhancers::charisma() const
{
    return this->_charisma;
}

const QPair<QString, int>& EveApi::AttributeEnhancers::perception() const
{
    return this->_perception;
}

const QPair<QString, int>& EveApi::AttributeEnhancers::willpower() const
{
    return this->_willpower;
}


const int& EveApi::AttributeEnhancers::intelligenceValue() const
{
    return this->_intelligence.second;
}

const int& EveApi::AttributeEnhancers::memoryValue() const
{
    return this->_memory.second;
}

const int& EveApi::AttributeEnhancers::charismaValue() const
{
    return this->_charisma.second;
}

const int& EveApi::AttributeEnhancers::perceptionValue() const
{
    return this->_perception.second;
}

const int& EveApi::AttributeEnhancers::willpowerValue() const
{
    return this->_willpower.second;
}


const QString& EveApi::AttributeEnhancers::intelligenceName() const
{
    return this->_intelligence.first;
}

const QString& EveApi::AttributeEnhancers::memoryName() const
{
    return this->_memory.first;
}

const QString& EveApi::AttributeEnhancers::charismaName() const
{
    return this->_charisma.first;
}

const QString& EveApi::AttributeEnhancers::perceptionName() const
{
    return this->_perception.first;
}

const QString& EveApi::AttributeEnhancers::willpowerName() const
{
    return this->_willpower.first;
}


EveApi::Attributes::Attributes(
    int intelligence, int memory, int charisma, int perception, int willpower) :
    _intelligence(intelligence),
    _memory(memory),
    _charisma(charisma),
    _perception(perception),
    _willpower(willpower)
{}

const int& EveApi::Attributes::intelligence() const
{
    return this->_intelligence;
}

const int& EveApi::Attributes::memory() const
{
    return this->_memory;
}

const int& EveApi::Attributes::charisma() const
{
    return this->_charisma;
}

const int& EveApi::Attributes::perception() const
{
    return this->_perception;
}

const int& EveApi::Attributes::willpower() const
{
    return this->_willpower;
}

