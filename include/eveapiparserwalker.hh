#ifndef __EVEAPIPARSERWALKER_HH__
#define __EVEAPIPARSERWALKER_HH__
#if !defined(EVEAPI_NO_PARSING)

#include "eveapiparser.hh"

class EveApiParserWalker: public EveApiParser
{
    Q_OBJECT
    public:
        EveApiParserWalker( QObject* parent = 0 );

        /*!
        Add a continuation request for journal walking

        \return The same identifier as passed in the id parameter
        */
        QString addRequest( QString id, QDomDocument doc );

    protected:
        //! map the IDs in the _continuationQueue to a pair of <processed request, unprocessed request>
        QMap<QString, QPair<QMap<int, QMap<QString, QString> >, QDomDocument> > _continuationStorage;

        //! map the IDs in the _incompleteQueue to processed requests
        QMap<QString, QMap<int, QMap<QString, QString> > > _incompleteStorage;

        /*!
        Allow the continuation queue to be checked in subclasses that use it
        */
        void checkContinuationQueue();

    private:
        /*!
        Method to be implemented by subclasses to connect signals and slots
        (as the return types from the parser will differ in each case, and
        cannot be defined generally here)
        */
        void setup();

    private slots:
        /*!
        Slot that stores incomplete requests in a incomplete request queue
        while the API fetches more data
        */
        void queueIncompleteRequest( QString id,
                                      QMap<int, QMap<QString, QString> > processedDoc,
                                      QPair<QString, QString> beforeID );

        /*!
        clean up after a completed request
        */
        void completeRequest( QString id,
                              QMap<int, QMap<QString, QString> > processedDoc );

    signals:
        /*!
        continue processing a pending request (used internally to tell the
        parser thread to begin with a new request)
        */
        void processPendingRequest( QString id,
                                    QDomDocument doc,
                                    QMap<int, QMap<QString, QString> > processedDoc );

        /*!
        notify the waiting object about the incomplete request
        */
        void incompleteRequest( QString id,
                                QMap<int, QMap<QString, QString> > processedDoc,
                                QPair<QString, QString> beforeID );

        /*!
        notify the waiting object about the complete request
        */
        void completedRequest( QString id,
                              QMap<int, QMap<QString, QString> > processedDoc );
};

#endif
#endif
