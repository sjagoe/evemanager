#ifndef __EVEAPICORPORATION_HH__
#define __EVEAPICORPORATION_HH__

#include "eveapiscope.hh"

class EveApiCorporation: public EveApiScope
{
    Q_OBJECT
    public:
        /*!
        create the child classes that provide API functionality
        */
        EveApiCorporation( QString& host, QString& dataPath, int& xmlIndent,
            QString& scope, QObject* parent = 0 );

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

        /*!
        access the MemberTracking api function
        */
        QString memberTracking( QMap<QString, QString>& parameters );

    protected slots:
        /*!
        This slot is called when an internal request is complete, so that it
        can be parsed
        */
        void internalRequestComplete( QString id, QDomDocument result, QString httpResponse, QDateTime cacheTime ){};

    private:
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

        /*!
        return the filename of the MemberTracking.xml request
        */
        static const QString memberTrackingRequestID()
        {
            return QString("MemberTracking.xml");
        }
};

#endif
