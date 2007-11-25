#ifndef __EVEAPIPARSEREVE_HH__
#define __EVEAPIPARSEREVE_HH__

#include <QThread>
#include <QMutex>

#include <QMap>

#include <QDateTime>

#include <boost/shared_ptr.hpp>

#include "eveapidatatype.hh"

using boost::shared_ptr;

class QDomDocument;

class EveApiCharacter;
class EveApiParserThread;
class EveApiDataBalance;

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
        shared_ptr<EveApiCharacter> _eveApi;

        //! Map request IDs to parsers
        QMap<QString, ParsedDataType> _requestIdToParserMap;

        //! Parsers
        QMap<ParsedDataType, shared_ptr<EveApiParserThread> > _parsers;

        /*!
        Create and set up the parsers
        */
        void setupParsers();

    private slots:
        /*!
        API request is complete (i.e. the XML has been received from the API
        */
        void apiRequestComplete( QString requestId,
                                 shared_ptr<QDomDocument> xmlDocument,
                                 QString httpResponse,
                                 QDateTime cacheExpireTime );

    signals:
        // all signals to be received externally
        /*!
        Emitted when a request fails (either at the API, or in parsing)
        */
        void requestFailed( QString id, QString error, QString httpResponse );

        /*!
        Emitted when the AccountBalance parser is complete
        */
        void accountBalanceComplete( QString parserId, shared_ptr<EveApiDataBalance> parsedData );

        // all signals used internally
        /*!
        Emitted to initiate the accountBalance parser
        */
        void parseAccountBalance( QString requestId, shared_ptr<QDomDocument> xmlDocument );
};

#endif
