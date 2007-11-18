#ifndef __EVEAPIPARSER_HH__
#define __EVEAPIPARSER_HH__
#if !defined(EVEAPI_NO_PARSING)

#include <QThread>

#include <QQueue>
#include <QPair>
#include <QMap>

#include <QString>
#include <QDomDocument>

#include <QSemaphore>

#include "eveapiparserthread.hh"

#include "eveapidata.hh"

#include "eveapidatatype.hh"

class EveApiParser: public QThread
{
        Q_OBJECT
    public:
        /*!
        Simply call the QThread constructor. All data initialisation has to
        happen in the run() method as we need an event loop.
        */
        EveApiParser( /*EveApiParserThread* newParser,*/ QObject* parent = 0 );

        /*!
        Destructor to clean up afterwards
        */
        ~EveApiParser();

        /*!
        Add a new request to the queue to be processed when the current one is
        complete

        \return a newly generated unique identifier
        */
        QString addRequest( ParsedDataType parserType, QDomDocument doc );

        /*!
        Add a continuation request for journal walking

        \return The same identifier as passed in the id parameter
        */
        QString addRequest( ParsedDataType parserType, QString parserId, QDomDocument doc );

    protected:
        //! Semaphore to keep track of pending requests
        QSemaphore _requestSemaphore;

        //! QQueue providing a request queue for new asynchronous processing
        QQueue<QString> _requestQueue;

        //! map the IDs in the _requestQueue to a QDomDocument
        QMap<QString, QDomDocument> _requestStorage;

        //! QQueue providing a request queue for continuation requests.
        QQueue<QString> _continuationQueue;

        //! map the IDs in the _continuationQueue to a pair of <processed request, unprocessed request>
        QMap<QString, QPair<EveApiData, QDomDocument> > _continuationStorage;

        //! map the IDs in the _incompleteQueue to processed requests
        QMap<QString, EveApiData> _incompleteStorage;

        /*!
        Create the dynamic objects in the thread, and execute the event loop.
        */
        void run();

        /*!
        Check if a request is queues, and if so, process it
        */
        void checkQueue();

//        /*!
//        Allow the continuation queue to be checked in subclasses that use it
//        */
//        void checkContinuationQueue();

    private:
        //! The objects that provide asynchronous processing of the data
//        EveApiParserThread* _parser;
        QMap<ParsedDataType, EveApiParserThread*> _parsers;

        /* !
        Method to be implemented by subclasses to connect signals and slots
        (as the return types from the parser will differ in each case, and
        cannot be defined generally here)
        */
        void setup();

        /*!
        create a unique identifier, using the object pointer "this", and the
        current Date/Time, ensuring that all requests, across all instances of
        the class have unique identifiers.
        */
        QString makeParserID();

    private slots:
        /*!
        Slot that stores incomplete requests in a incomplete request queue
        while the API fetches more data
        */
        void queueIncompleteRequest( QString parserId,
                                     EveApiData processedDoc,
                                     QPair<QString, QString> beforeID );

        /*!
        clean up after a completed request
        */
        void completeRequest( QString parserId,
                              EveApiData processedDoc );

    signals:
        /*!
        process a new request (used internally to tell the parser thread to
        begin with a new request)
        */
        void processNewRequest( QString parserId, QDomDocument doc );

        /*!
        continue processing a pending request (used internally to tell the
        parser thread to begin with a new request)
        */
        void processPendingRequest( QString parserId,
                                    QDomDocument doc,
                                    EveApiData processedDoc );

        /*!
        notify the waiting object about the incomplete request
        */
        void incompleteRequest( QString id, EveApiData processedDoc,
                                QPair<QString, QString> beforeID );

        /*!
        notify the waiting object about the complete request
        */
        void completedRequest( QString id, EveApiData processedDoc );
};

#endif
#endif
