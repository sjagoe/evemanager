
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

#ifndef __ABSTRACTEVEAPIDATA_HH__
#define __ABSTRACTEVEAPIDATA_HH__

#include <QList>
#include <QMap>
#include <QString>
#include <QStringList>

#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

namespace EveApi
{
    class NoSuchColumn {};

    /*!  The basic item of data, to abstract the storage and
      representation away from the larger structures
     */
    class DataItem
    {
    public:
	DataItem() {};

	DataItem(const QString& data)
	{
	    this->_data = data;
	};

	void set(const QString& data)
	{
	    this->_data = data;
	};

	const QString& get() const
	{
	    return this->_data;
	};

    private:
	QString _data;
    };

    class RowSet;
    template <class> class Row;

    /*!  Represent a basic <rowset> element in the xml.  Contains rows
         that can contain other RowSets.
     */
    class RowSet
    {
    public:
	RowSet(const QString& name,
	       const QString& key,
	       const QStringList& columns)
	{
	    this->_name = name;
	    this->_key = key;
	    this->_columns = columns;
	};

	/*!  Add a row to the table
	 */
	shared_ptr<Row<RowSet> > add_row(const QMap<QString, DataItem>& values);

	QList<shared_ptr<Row<RowSet> > >::const_iterator begin() const;

	QList<shared_ptr<Row<RowSet> > >::const_iterator end() const;

	const shared_ptr<Row<RowSet> >& row(const QString& key) const;

    private:
	//! Name of the rowset
	QString _name;

	//! Name of the keyed column of the table
	QString _key;

	//! Columns in the table
	QStringList _columns;

	//! A mapping of table's key element to row.  Assumes keys are
	//! unique
	QMap<QString, shared_ptr<Row<RowSet> > > _rowsByKey;

	//! All rows in the RowSet, in the order represented in xml
	QList<shared_ptr<Row<RowSet> > > _rowsInOrder;
    };

    template <class T>
    class Row
    {
    public:
	Row(const QMap<QString, DataItem>& values)
	{
	    this->_values = values;
	};

	const T& get_child() const
	{
	    return this->_child;
	};

	void add_child(shared_ptr<T> child) {};

	const DataItem& operator[](const QString& column) const
	{
	    if (! this->_values.contains(column))
	    {
		throw NoSuchColumn();
	    }
	    return this->_values.value(column)
	};

    private:
	QMap<QString, DataItem> _values;

	shared_ptr<T> _child;
    };
};

#endif
