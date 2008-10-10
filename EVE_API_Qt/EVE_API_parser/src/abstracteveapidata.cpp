
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

#include "abstracteveapidata.hh"

EveApi::DataItem::DataItem() {};

EveApi::DataItem::DataItem(const QString& data)
{
    this->_data = data;
};

void EveApi::DataItem::set(const QString& data)
{
    this->_data = data;
};

const QString& EveApi::DataItem::get() const
{
    return this->_data;
};


EveApi::RowSet::RowSet(const QString& name,
		       const QString& key,
		       const QStringList& columns)
{
    this->_name = name;
    this->_key = key;
    this->_columns = columns;
};

/*!  Add a row to the table
 */
shared_ptr<EveApi::Row<EveApi::RowSet> > EveApi::RowSet::add_row(const QMap<QString, DataItem>& values)
{

}

QList<shared_ptr<EveApi::Row<EveApi::RowSet> > >::const_iterator EveApi::RowSet::begin() const
{

}

QList<shared_ptr<EveApi::Row<EveApi::RowSet> > >::const_iterator EveApi::RowSet::end() const
{

}

const shared_ptr<EveApi::Row<EveApi::RowSet> >& EveApi::RowSet::row(const QString& key) const
{

}


template <class T>
EveApi::Row<T>::Row(const QMap<QString, EveApi::DataItem>& values)
{
    this->_values = values;
};

template <class T>
const T& EveApi::Row<T>::get_child() const
{
    return this->_child;
};

template <class T>
void EveApi::Row<T>::add_child(shared_ptr<T> child)
{

}

template <class T>
const EveApi::DataItem& EveApi::Row<T>::operator[](const QString& column) const throw(NoSuchColumn)
{
    if (! this->_values.contains(column))
    {
	throw NoSuchColumn();
    }
    return this->_values.value(column);
};
