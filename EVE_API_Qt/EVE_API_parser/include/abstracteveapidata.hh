
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

#include <QList>
#include <QMap>
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

    //    class RowSet;
    //    template <class> class Row;
    //
    //    /*!  Represent a basic <rowset> element in the xml.  Contains rows
    //      that can contain other RowSets.
    //    */
    //    class RowSet
    //    {
    //    public:
    //        RowSet();
    //

    //
    //        /*!
    //          Set the name of the rowset
    //         */
    //        void set_name(const QString& name) throw(ImmutableError);
    //
    //        void set_key(const QString& key) throw(ImmutableError);
    //
    //        void set_columns(const QStringList& columns) throw(ImmutableError);
    //
    //    private:

    //    };
    //
    //    template <class T> class Row
    //    {
    //    public:
    //        Row(const QMap<QString, DataItem>& values);
    //
    //        const T& get_child() const;
    //
    //        void add_child(shared_ptr<T> child);
    //
    //        const DataItem& operator[](const QString& column) const throw(NoSuchColumn);
    //
    //    private:
    //        QMap<QString, DataItem> _values;
    //
    //        shared_ptr<T> _child;
    //    };

    template <class T> class Row;
    template <class T> class Rowset;

    template <class T> class Row
    {
    private:
        template <class U> class InternalRowset: public Rowset<U>
        {
        public:
            InternalRowset(int levels)
            {
                this->_row = new Row<T>(levels - 1);
            }
        };

    public:
        Row(int levels=0)
        {
            this->_levels = levels;
            if (levels > 0)
            {
                this->_childRowset = new InternalRowset<T>(levels);
                this->_childDirect = 0;
            }
            else
            {
                this->_childRowset = 0;
                this->_childDirect = new T;
            }
        }

        ~Row()
        {
            if (this->_childRowset)
            {
                delete this->_childRowset;
            }
            if (this->_childDirect)
            {
                delete this->_childDirect;
            }
        }

        T* getChild()
        {
            return this->_childDirect;
        }

        InternalRowset<T>* getChildRowset()
        {
            return this->_childRowset;
        }

        int getLevels()
        {
            return this->_levels;
        }

        bool hasRowset()
        {
            return (this->getLevels() > 0);
        }

    private:
        //! Number of levels of Rowses nested in this Row
        int _levels;

        //! Nested Rowset
        InternalRowset<T>* _childRowset;

        //! Child if no nested Rowset
        T* _childDirect;
    };

    template <class T> class Rowset
    {
    public:
        /*!
          Construct a Rowset with required attributes
         */
        Rowset(const QString& name,
               const QString& key,
               const QStringList& columns)
        {
            this->_name = name;
            this->_key = key;
            this->_columns = columns;
        }

        ~Rowset()
        {
        }

        /*!
          Add a row to the table
         */
        Row<T>* add_row(const QMap<QString, DataItem>& values)
        {
            Row<T>* row = 0;
            if (values.contains(this->_key))
            {
                DataItem key_ = values.value(this->_key);
                QString key = key_.get();
                row = new Row<T>(values);
                this->_rowsByKey.insert(key, row);
                this->_rowsInOrder.append(row);
            }
            return row;
        }

//        /*!
//          Get an iterator at the start of the ordered list of rows
//         */
//        QList<Row<T>* >::ConstIterator begin() const
//        {
//            return this->_rowsInOrder.begin();
//        }
//
//        /*!
//          Get an iterator at the end of the ordered list of rows
//         */
//        QList<Row<T>* >::ConstIterator end() const
//        {
//            return this->_rowsInOrder.end();
//        }

        QList<Row<T>* >& rowsInOrder()
        {
            return this->_rowsInOrder;
        }

        /*!
          Get a row by the value of its key
         */
        const Row<T>* row(const QString& key) const
        {
            return this->_rowsByKey.value(key);
        }

        /*!
          Get a row by the value of its key
         */
        const Row<T>* operator[](const QString& key) const
        {
            return this->_rowsByKey.value(key);
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
        QMap<QString, Row<T>* > _rowsByKey;

        //! All rows in the RowSet, in the order represented in xml
        QList<Row<T>* > _rowsInOrder;
    };

};

#endif
