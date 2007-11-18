#ifndef __EVEAPIPARSEREVE_HH__
#define __EVEAPIPARSEREVE_HH__

#include <QThread>
#include <QMutex>

#include <QMap>

#include "eveapidatatype.hh"

class EveApiCharacter;

class EveApiParserCharacter: public QThread
{
    Q_OBJECT
    public:
        /*!
        call QThread constructor, and construct objects that belong to the
        main thread.
        */
        EveApiParserCharacter( QString& host, QString& dataPath, int& xmlIndent,
            QString& scope, QObject* parent = 0 );

//        /*!
//        Create a new request for the Journal
//        */
//        QString walletJournal();

        /*!
        create a new request for the account balance
        */
        QString accountBalance( QMap<QString, QString>& parameters );

    protected:
        /*!
        create actual parser objects, and start the event loop
        */
        void run();

    private:
        //! Mutex to protect the API should it be used in a threaded environment
        QMutex _apiMutex;

        //! The Char interface of the EVE API
        EveApiCharacter* _eveApi;

        //! Map request IDs to parsers
        QMap<QString, ParsedDataType> _requestIdToParserMap;
};

#endif
