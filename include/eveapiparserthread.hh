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
        virtual void processRequest( QString id, QDomDocument doc ) = 0;
};

#endif
