#ifndef __EVEAPICHARACTER_HH__
#define __EVEAPICHARACTER_HH__

#include <QMap>
#include <QString>
#include <QPair>

#include "eveapiscope.hh"

#if !defined(EVEAPI_NO_PARSING)
#include "eveapidata_walked.hh"
class EveApiParser;
#endif

class EveApiCharacter: public EveApiScope
{
    Q_OBJECT
    public:
        /*!
        create the child classes that provide API functionality
        */
        EveApiCharacter( QString& host, QString& dataPath, int& xmlIndent,
            QString& scope, QObject* parent = 0 );

        /*!
        access the CharacterSheet api function
        */
        QString characterSheet( QMap<QString, QString>& parameters );

        /*!
        access the SkillInTraining api function
        */
        QString skillInTraining( QMap<QString, QString>& parameters );

        /*!
        access the WalletJournal api function
        */
        QString walletJournal( QMap<QString, QString>& parameters );

        /*!
        access the WalletTransactions api function
        */
        QString walletTransactions( QMap<QString, QString>& parameters );

        /*!
        access the AccountBalance api function
        */
        QString accountBalance( QMap<QString, QString>& parameters );

#if !defined(EVEAPI_NO_PARSING)
        /*!
        access the WalletJournal api function, and provide a parse,
        fully 'walked' output
        */
        QString walletJournalParsed( QMap<QString, QString>& parameters );

    protected slots:
        /*!
        This slot is called when an internal request is complete, so that it
        can be parsed
        */
        void internalRequestComplete( QString requestId, QDomDocument result, QString httpResponse, QDateTime cacheTime );

    private:
        //! Parser for the Journal/Transaction walking
        EveApiParser* _parserWalker;

        //! QMap to map the api request ID to a parser
        QMap<QString, EveApiParser*> _requestIdToParserMap;

        //! QMap to map the api request ID to a request, which can be used to
        //! determine the request via the parser ID to request ID map
        QMap<QString, QString> _requestIdToRequestMap;

        //! QMap to map the parser ID to an api request ID
        QMap<QString, QString> _parserIdToRequestIdMap;

        //! QMap to map an api request ID to a parser ID
        QMap<QString, QString> _requestIdToParserIdMap;

        //! QMap to map request ID to request parameters
        QMap<QString, QMap<QString, QString> > _requestIdToRequestParametersMap;

        /*!
        Create all parsers
        */
        void createParsers();
#else
    private:
#endif
        /*!
        Create request objects
        */
        void createRequest( QString& requestId,
                            QStringList& requiredParams,
                            QStringList& optionalParams,
                            QStringList& cacheId );

        /*!
        create all requests (delegated from the constructor)
        */
        void createRequests();

        /*!
        return the filename of the Sovereignty.xml request
        */
        static const QString characterSheetRequestID()
        {
            return QString("CharacterSheet.xml");
        };

        /*!
        return the filename of the SkillInTraining.xml request
        */
        static const QString skillInTrainingRequestID()
        {
            return QString("SkillInTraining.xml");
        };

        /*!
        return the filename of the WalletJournal.xml request
        */
        static const QString walletJournalRequestID()
        {
            return QString("WalletJournal.xml");
        };

        /*!
        return the filename of the WalletTransactions.xml request
        */
        static const QString walletTransactionsRequestID()
        {
            return QString("WalletTransactions.xml");
        };

        /*!
        return the filename of the AccountBalance.xml request
        */
        static const QString accountBalanceRequestID()
        {
            return QString("AccountBalance.xml");
        };

#if !defined(EVEAPI_NO_PARSING)
    private slots:
        // slots for the walker parser:
        /*!
        Receive journal signal that parsing requires more info
        */
        void walkerRequestIncomplete( QString parserId,
                                EveApiDataWalked processedDoc,
                                QPair<QString, QString> beforeID );

        /*!
        Receive journal walking signal that the parsing is complete
        */
        void walkerRequestComplete( QString parserId,
                              EveApiDataWalked processedDoc );

    signals:
        /*!
        notify that a journal walking has been completed
        */
        void journalWalkerRequestComplete( QString requestId,
                                EveApiDataWalked processedDoc );
#endif
};

#endif
