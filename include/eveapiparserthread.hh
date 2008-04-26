
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

#ifndef __EVEAPIPARSERTHREAD_HH__
#define __EVEAPIPARSERTHREAD_HH__

#include <QObject>
#include <QMutex>
//#include <QDomDocument>
#include <QString>
#include <QQueue>
#include <QPair>
#include <QDateTime>

#include <boost/shared_ptr.hpp>

#include "eveapidatatype.hh"

using boost::shared_ptr;

class QDomDocument;

class EveApiParserThread: public QObject
{
    Q_OBJECT
    public:
        //! set up the parser
        EveApiParserThread( ParsedDataType thisType, QObject* parent = 0 );

        /*!
        return the parser type
        */
        const ParsedDataType& type() const;

    public slots:
        /*!
        Start the parser
        */
        void parse( QString parserId, shared_ptr<QDomDocument> doc );

    protected:
        /*!
        getTime
        */
        QDateTime apiDateTimeToQDateTime( QString& apiDateTime );

        /*!
        Perform the actual parsing of the data, and emit a signal when done.
        The signal must be defined in the subclass
        */
        virtual void doParse( const QString& parserId, shared_ptr<QDomDocument> doc ) = 0;

    private:
//        //! Semaphore telling the number of requests to be parsed (including the current request)
//        QSemaphore _queueSize;

        //! Mutex to ensure that only one request can be started at a time
        QMutex _parserMutex;

        //! The type of data the parser can parse
        ParsedDataType _type;

//        //! The ID of the request being handled
//        QString _currentParserId;
//
//        //! Queue requests until they can be completed
//        QQueue<QPair<QString, QDomDocument> > _parserQueue;
    signals:
        void requestFailed( QString id, QString error, QString httpResponse );
};

#endif
