#ifndef __EVEAPIPARSERTHREAD_HH__
#define __EVEAPIPARSERTHREAD_HH__
#if !defined(EVEAPI_NO_PARSING)

#include <QObject>

#include <QString>
#include <QDomDocument>

#include <QMap>
#include <QPair>

#include "eveapidata.hh"

class EveApiParserThread: public QObject
{
        Q_OBJECT
    public:
        /*!
        call the QObject constructor
        */
        EveApiParserThread( QObject* parent = 0 );

    public slots:
        /*!
        process a new request
        */
        virtual void processRequest( QString id, QDomDocument doc ) = 0;

        /*!
        continue processing an old request
        */
        virtual void processRequest( QString id,
                             QDomDocument doc,
                             EveApiData processedDoc ) = 0;

    signals:
        /*!
        Signal emitted when a document is processed, and the API will provide
        no further data.
        */
        void documentProcessed( QString id,
                                EveApiData processedDoc );

        /*!
        Signal emitted if their could be more data from the API, but the current
        set is fully processed
        */
        void incompleteDocument( QString id,
                                 EveApiData processedDoc,
                                 QPair<QString, QString> beforeID );
};

#endif
#endif
