#ifndef __EVEAPICOMMON_HH__
#define __EVEAPICOMMON_HH__

#include <QMap>
#include <QString>
#include <QPair>

#include "eveapiscope.hh"


class EveApiCommon: public EveApiScope
{
    public:
        EveApiCommon( QString& host,
                      QString& dataPath,
                      int& xmlIndent,
                      QString& scope,
                      const int& proxyType,
                      const QString& proxyHost,
                      const quint16& proxyPort,
                      const QString & proxyUser,
                      const QString & proxyPassword,
                      QObject* parent = 0 );

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
        access the IndustryJobs api function
        */
        QString industryJobs( QMap<QString, QString>& parameters );

        /*!
        access the AssetList api function
        */
        QString assetList( QMap<QString, QString>& parameters );

        /*!
        access the KillLog api function
        */
        QString killLog( QMap<QString, QString>& parameters );

        /*!
        access the MarketOrders api function
        */
        QString marketOrders( QMap<QString, QString>& parameters );

    protected:
        /*!
        Create request objects
        */
        void createRequest( QString& requestId,
                            QStringList& requiredParams,
                            QStringList& optionalParams,
                            QStringList& cacheId,
                            const int& p_type,
                            const QString& host,
                            const quint16& port,
                            const QString & user,
                            const QString & password );

    private:
        /*!
        create all requests (delegated from the constructor)
        */
        void createCommonRequests( const int& proxyType,
                                   const QString& proxyHost,
                                   const quint16& proxyPort,
                                   const QString & proxyUser,
                                   const QString & proxyPassword );

        /*!
        return the filename of the WalletJournal.xml request
        */
        static const QString walletJournalRequestID()
        {
            return QString( "WalletJournal.xml" );
        };

        /*!
        return the filename of the WalletTransactions.xml request
        */
        static const QString walletTransactionsRequestID()
        {
            return QString( "WalletTransactions.xml" );
        };

        /*!
        return the filename of the AccountBalance.xml request
        */
        static const QString accountBalanceRequestID()
        {
            return QString( "AccountBalance.xml" );
        };

        /*!
        return thefilename of the IndustryJobs.xml request
        */
        static const QString industryJobsRequestID()
        {
            return QString( "IndustryJobs.xml" );
        };

        /*!
        return thefilename of the AssetList.xml request
        */
        static const QString assetListRequestID()
        {
            return QString( "AssetList.xml" );
        };

        /*!
        return the filename of the KillLog.xml request
        */
        static const QString killLogRequestID()
        {
            return QString( "KillLog.xml" );
        };

        /*!
        return the filename of the MarketOrders.xml request
        */
        static const QString marketOrdersRequestID()
        {
            return QString( "MarketOrders.xml" );
        };
};


#endif
