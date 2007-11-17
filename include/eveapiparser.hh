#ifndef __EVEAPIPARSER_HH__
#define __EVEAPIPARSER_HH__

#include <QThread>

#include <QQueue>
#include <QPair>
#include <QMap>

#include <QString>
#include <QDomDocument>

#include <QSemaphore>

class EveApiParserThread;

class EveApiParser: public QThread
{
        Q_OBJECT
    public:
        /*!
        Simply call the QThread constructor. All data initialisation has to
        happen in the run() method as we need an event loop.
        */
        EveApiParser( EveApiParserThread* parser, QObject* parent = 0 );

        /*!
        Add a new request to the queue to be processed when the current one is
        complete

        \return a newly generated unique identifier
        */
        QString addRequest( QDomDocument doc );

        /*!
        Add a continuation request for journal walking

        \return The same identifier as passed in the id parameter
        */
        virtual QString addRequest( QString id, QDomDocument doc ) = 0;

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
        QMap<QString, QPair<QMap<int, QMap<QString, QString> >, QDomDocument> > _continuationStorage;

        //! map the IDs in the _incompleteQueue to processed requests
        QMap<QString, QMap<int, QMap<QString, QString> > > _incompleteStorage;

        //! The object that provides asynchronous processing of the data
        EveApiParserThread* _parser;

        /*!
        Create the dynamic objects in the thread, and execute the event loop.
        */
        void run();

        /*!
        Check if a request is queues, and if so, process it
        */
        void checkQueue();

        virtual void checkContinuationQueue() {};

    private:
        /*!
        Method to be implemented by subclasses to connect signals and slots
        (as the return types from the parser will differ in each case, and
        cannot be defined generally here)
        */
        virtual void setup() = 0;

        /*!
        create a unique identifier, using the object pointer "this", and the
        current Date/Time, ensuring that all requests, across all instances of
        the class have unique identifiers.
        */
        QString makeID();

//    private slots:
//        /*!
//        Slot that stores incomplete requests in a incomplete request queue
//        while the API fetches more data
//        */
//        void queueIncompleteRequest( QString id,
//                                      QMap<int, QMap<QString, QString> > processedDoc,
//                                      QPair<QString, QString> beforeID );
//
//        /*!
//        clean up after a completed request
//        */
//        void completeRequest( QString id,
//                              QMap<int, QMap<QString, QString> > processedDoc );

    signals:
        /*!
        process a new request
        */
        void processNewRequest( QString id, QDomDocument doc );

//        /*!
//        continue processing a pending request
//        */
//        void processPendingRequest( QString id,
//                                    QDomDocument doc,
//                                    QMap<int, QMap<QString, QString> > processedDoc );
//
//        /*!
//        notify the waiting object about the incomplete request
//        */
//        void incompleteRequest( QString id,
//                                QMap<int, QMap<QString, QString> > processedDoc,
//                                QPair<QString, QString> beforeID );
//
//        /*!
//        notify the waiting object about the complete request
//        */
//        void completedRequest( QString id,
//                              QMap<int, QMap<QString, QString> > processedDoc );
};

#endif
