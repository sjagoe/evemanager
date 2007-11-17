#ifndef __EVEAPIPARSERTHREAD_HH__
#define __EVEAPIPARSERTHREAD_HH__

#include <QObject>

#include <QString>
#include <QDomDocument>

#include <QMap>
#include <QPair>

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
