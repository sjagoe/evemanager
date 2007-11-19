#ifndef __EVEAPIPARSERTHREAD_HH__
#define __EVEAPIPARSERTHREAD_HH__

#include <QObject>
#include <QMutex>
#include <QDomDocument>
#include <QString>
#include <QQueue>
#include <QPair>

#include "eveapidatatype.hh"

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
        void parse( const QString& parserId, const QDomDocument& doc );

    protected:
        /*!
        Perform the actual parsing of the data, and emit a signal when done.
        The signal must be defined in the subclass
        */
        virtual void doParse( const QString& parserId, const QDomDocument& doc ) = 0;

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
};

#endif
