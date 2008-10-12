
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

#include "charactersheetdata.hh"

EveApi::AttributeEnhancers::AttributeEnhancers()
{}

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


const QPair<QString, int>& EveApi::AttributeEnhancers::get_intelligence() const
{
    return this->_intelligence;
}

const QPair<QString, int>& EveApi::AttributeEnhancers::get_memory() const
{
    return this->_memory;
}

const QPair<QString, int>& EveApi::AttributeEnhancers::get_charisma() const
{
    return this->_charisma;
}

const QPair<QString, int>& EveApi::AttributeEnhancers::get_perception() const
{
    return this->_perception;
}

const QPair<QString, int>& EveApi::AttributeEnhancers::get_willpower() const
{
    return this->_willpower;
}


const int& EveApi::AttributeEnhancers::get_intelligenceValue() const
{
    return this->_intelligence.second;
}

const int& EveApi::AttributeEnhancers::get_memoryValue() const
{
    return this->_memory.second;
}

const int& EveApi::AttributeEnhancers::get_charismaValue() const
{
    return this->_charisma.second;
}

const int& EveApi::AttributeEnhancers::get_perceptionValue() const
{
    return this->_perception.second;
}

const int& EveApi::AttributeEnhancers::get_willpowerValue() const
{
    return this->_willpower.second;
}


const QString& EveApi::AttributeEnhancers::get_intelligenceName() const
{
    return this->_intelligence.first;
}

const QString& EveApi::AttributeEnhancers::get_memoryName() const
{
    return this->_memory.first;
}

const QString& EveApi::AttributeEnhancers::get_charismaName() const
{
    return this->_charisma.first;
}

const QString& EveApi::AttributeEnhancers::get_perceptionName() const
{
    return this->_perception.first;
}

const QString& EveApi::AttributeEnhancers::get_willpowerName() const
{
    return this->_willpower.first;
}


void EveApi::AttributeEnhancers::set_intelligence(
    const QPair<QString, int>& intelligence)
{
    this->_intelligence = intelligence;
}

void EveApi::AttributeEnhancers::set_memory(const QPair<QString, int>& memory)
{
    this->_memory = memory;
}

void EveApi::AttributeEnhancers::set_charisma(
    const QPair<QString, int>& charisma)
{
    this->_charisma = charisma;
}

void EveApi::AttributeEnhancers::set_perception(
    const QPair<QString, int>& perception)
{
    this->_perception = perception;
}

void EveApi::AttributeEnhancers::set_willpower(
    const QPair<QString, int>& willpower)
{
    this->_willpower = willpower;
}


EveApi::Attributes::Attributes() :
    _intelligence(0),
    _memory(0),
    _charisma(0),
    _perception(0),
    _willpower(0)
{}

EveApi::Attributes::Attributes(
    int intelligence, int memory, int charisma, int perception, int willpower) :
    _intelligence(intelligence),
    _memory(memory),
    _charisma(charisma),
    _perception(perception),
    _willpower(willpower)
{}


const int& EveApi::Attributes::get_intelligence() const
{
    return this->_intelligence;
}

const int& EveApi::Attributes::get_memory() const
{
    return this->_memory;
}

const int& EveApi::Attributes::get_charisma() const
{
    return this->_charisma;
}

const int& EveApi::Attributes::get_perception() const
{
    return this->_perception;
}

const int& EveApi::Attributes::get_willpower() const
{
    return this->_willpower;
}

