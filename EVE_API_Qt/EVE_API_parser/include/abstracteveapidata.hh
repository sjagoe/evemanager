
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

#ifndef _EVEAPI_ABSTRACTEVEAPIDATA_HH_
#define _EVEAPI_ABSTRACTEVEAPIDATA_HH_

#include <QDateTime>
#include <QList>
#include <QMap>
#include <QObject>
#include <QString>
#include <QStringList>

#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

namespace EveApi
{
    class NoSuchColumn {};

    class NoSuchRow {};

    class ImmutableError : public QString
    {
    public:
        ImmutableError(const char* args) :
                QString(args) {};
    };

    /*!  The basic item of data, to abstract the storage and
      representation away from the larger structures.

      TODO: Needs to be able to determine if the DataItem is null.
    */
    class DataItem
    {
    public:
        DataItem();

        DataItem(const QString& data);

        void set(const QString& data);

        const QString& get() const;

    private:
        QString _data;
    };

    class AbstractData
    {
    public:
        AbstractData( const int& version,
                      const QDateTime& currentTime,
                      const QDateTime& cachedUntil ):
        _version(version),
        _currentTime(currentTime),
        _cachedUntil(cachedUntil)
        {}

        const int& getVersion()
        {
            return this->_version;
        }

        const QDateTime& getServerTime()
        {
            return this->_currentTime;
        }

        const QDateTime& getCachedUntilTime()
        {
            return this->_cachedUntil;
        }

    private:
        //! Version of the API where the result is available
        int _version;

        //! Time on the server when the result was fetched
        QDateTime _currentTime;

        //! time that the cache expires and new data is available
        QDateTime _cachedUntil;
    };

    template <class X> class Row;
    template <class X> class Rowset;

    template <class X> class Row
    {
    private:
        template <class Y> class InternalRowset: public Rowset<Y>
        {
        public:
            InternalRowset( const QString& name,
                            const QString& key,
                            const QStringList& columns,
                            Row<X>* parent=0):
            Rowset<Y>(name, key, columns, parent)
            {}
        };

    public:
        Row(const QMap<QString, DataItem>& values, Rowset<X>* parent=0)
        {
            this->_parent = parent;
            this->_values = values;
            this->_childRowset = 0;
            this->_childDirect = 0;
            this->_subLevels = 0;
        }

        ~Row()
        {
            this->_parent = 0;
            if (this->_childRowset)
            {
                delete this->_childRowset;
            }
            if (this->_childDirect)
            {
                delete this->_childDirect;
            }
        }

        const DataItem& operator[](const QString& column) const throw(NoSuchColumn)
        {
            if (! this->_values.contains(column))
            {
                throw NoSuchColumn();
            }
            return this->_values.value(column);
        }

        X* addChild()
        {
            if (this->_childRowset != 0)
            {
                this->_childDirect = new X;
            }
            return this->getChild();
        }

        X* getChild()
        {
            return this->_childDirect;
        }

        bool hasChild()
        {
            return (this->_childDirect != 0);
        }

        Rowset<X>* addChildRowset(const QString& name,
                                  const QString& key,
                                  const QStringList& columns)
        {
            if (this->_childDirect != 0)
            {
                this->_childRowset = new InternalRowset<X>(name, key, columns, this);
                this->childAdded();
            }
            return this->getChildRowset();
        }

        Rowset<X>* getChildRowset()
        {
            return static_cast<Rowset<X>* >(this->_childRowset);
        }

        bool hasRowset()
        {
            return (this->_childRowset != 0);
        }

        int getLevels()
        {
            return this->_levels;
        }

        void childAdded()
        {
            this->_subLevels++;
            if (this->_parent)
            {
                this->_parent->childAdded();
            }
        }

    private:
        //! Number of levels of Rowsets nested in this Row
        int _subLevels;

        //! Values contained in the row
        QMap<QString, DataItem> _values;

        //! Nested Rowset
        InternalRowset<X>* _childRowset;

        //! Child if no nested Rowset
        X* _childDirect;

        //! parent rowset
        Rowset<X>* _parent;
    };

    template <class X> class Rowset
    {
    public:
        /*!
          Construct a Rowset with required attributes
         */
        Rowset( const QString& name,
                const QString& key,
                const QStringList& columns,
                Row<X>* parent=0)
        {
            this->_parent = parent;
            this->_subLevels = 0;
            this->_name = name;
            this->_key = key;
            this->_columns = columns;
        }

        virtual ~Rowset()
        {
            this->_parent = 0;
            QString key;
            foreach (key, this->_rowsByKey.keys())
            {
                Row<X>* row = this->_rowsByKey.take(key);
                delete row;
            }
            this->_rowsByKey.clear();
            this->_rowsInOrder.clear();
        }

        /*!
          Add a row to the table
         */
        Row<X>* addRow(const QMap<QString, DataItem>& values)
        {
            Row<X>* row = 0;
            if (values.contains(this->_key))
            {
                DataItem key_ = values.value(this->_key);
                QString key = key_.get();
                row = new Row<X>(values, this);
                this->_rowsByKey.insert(key, row);
                this->_rowsInOrder.append(row);
            }
            return row;
        }

//        /*!
//          Get an iterator at the start of the ordered list of rows
//         */
//        QList<Row<X>* >::ConstIterator begin() const
//        {
//            return this->_rowsInOrder.begin();
//        }

//        /*!
//          Get an iterator at the end of the ordered list of rows
//         */
//        QList<Row<X>* >::ConstIterator end() const
//        {
//            return this->_rowsInOrder.end();
//        }

        QList<Row<X>* >* rowsInOrder()
        {
            return this->_rowsInOrder;
        }

        /*!
          Get a row by the value of its key
         */
        const Row<X>* row(const QString& key) const
        {
            return this->_rowsByKey.value(key);
        }

        /*!
          Get a row by the value of its key
         */
        const Row<X>* operator[](const QString& key) const
        {
            return this->_rowsByKey.value(key);
        }

        void childAdded()
        {
            this->_subLevels++;
            if (this->_parent)
            {
                this->_parent->childAdded();
            }
        }

    protected:
        //! Name of the rowset
        QString _name;

        //! Name of the keyed column of the table
        QString _key;

        //! Columns in the table
        QStringList _columns;

        //! A mapping of table's key element to row.  Assumes keys are
        //! unique
        QMap<QString, Row<X>* > _rowsByKey;

        //! All rows in the RowSet, in the order represented in xml
        QList<Row<X>* > _rowsInOrder;

        //! Nested sub-levels
        int _subLevels;

    private:
        //! parent
        Row<X>* _parent;
    };

}

#endif
