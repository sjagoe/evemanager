#ifndef __EVEAPIPARSERWALKERTHREAD_HH__
#define __EVEAPIPARSERWALKERTHREAD_HH__
#if !defined(EVEAPI_NO_PARSING)

#include "eveapiparserthread.hh"

class EveApiParserWalkerThread: public EveApiParserThread
{
    Q_OBJECT
    public:
        EveApiParserWalkerThread( QObject* parent = 0 );

    public slots:
        /*!
        process a new request
        */
        void processRequest( QString id,
                             QDomDocument doc );

        /*!
        continue processing an old request
        */
        void processRequest( QString id,
                             QDomDocument doc,
                             QMap<int, QMap<QString, QString> > processedDoc );

    private:
        /*!
        Provide the actual XML parsing functionality
        */
        QPair<QString, QString> processSegment( QDomDocument doc,
                QMap<int, QMap<QString, QString> >& processedDoc );

    signals:
        /*!
        Signal emitted when a document is processed, and the API will provide
        no further data.
        */
        void documentProcessed( QString id,
                                QMap<int, QMap<QString, QString> > processedDoc );

        /*!
        Signal emitted if their could be more data from the API, but the current
        set is fully processed
        */
        void incompleteDocument( QString id,
                                 QMap<int, QMap<QString, QString> > processedDoc,
                                 QPair<QString, QString> beforeID );
};

#endif
#endif
