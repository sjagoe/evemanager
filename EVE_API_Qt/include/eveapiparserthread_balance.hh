
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

#ifndef __EVEAPIPARSERTHREAD_BALANCE_HH__
#define __EVEAPIPARSERTHREAD_BALANCE_HH__

#include <QDateTime>

#include <boost/shared_ptr.hpp>

#include "eveapiparserthread.hh"

using boost::shared_ptr;

class QDomDocument;
class QDomNode;

class EveApiDataBalance;

class EveApiParserThreadBalance: public EveApiParserThread
{
    Q_OBJECT
    public:
        /*!
        Construct the parser
        */
        EveApiParserThreadBalance( QObject* parent = 0 );

    protected:
        /*!
        Perform the actual parsing of the data, and emit a signal when done.
        The signal must be defined in the subclass
        */
        void doParse( const QString& parserId, const shared_ptr<QDomDocument> doc );

    private:
        /*!
        parse a "rowset" in the account balance data
        */
        void parseRowSet( QDomNode* rowset, shared_ptr<EveApiDataBalance>& data );

    signals:
        /*!
        This signal is emitted when parsing is complete
        */
        void parsingComplete( QString parserId, shared_ptr<EveApiDataBalance> parsedData );
};

#endif
