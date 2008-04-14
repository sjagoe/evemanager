#ifndef __EVEAPIMAP_HH__
#define __EVEAPIMAP_HH__

#include "eveapiscope.hh"

class EveApiMap: public EveApiScope
{
        Q_OBJECT
    public:
        /*!
        create the child classes that provide API functionality
        */
        EveApiMap( QString& host,
                   QString& dataPath,
                   int& xmlIndent,
                   QString& scope,
                   const int& proxyType,
                   const QString & proxyHost,
                   const quint16 & proxyPort,
                   const QString & proxyUser,
                   const QString & proxyPassword,
                   QObject* parent = 0 );

        /*!
        access the Sovereignty api function
        */
        QString sovereignty( QMap<QString, QString>& parameters );

        /*!
        access the Jumps api function
        */
        QString jumps( QMap<QString, QString>& parameters );

        /*!
        access the Kills api function
        */
        QString kills( QMap<QString, QString>& parameters );

    private:
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

        /*!
        create all requests (delegated from the constructor)
        */
        void createRequests( const int& proxyType,
                             const QString & proxyHost,
                             const quint16 & proxyPort,
                             const QString & proxyUser,
                             const QString & proxyPassword );

        /*!
        return the filename of the Sovereignty.xml request
        */
        static const QString sovereigntyRequestID()
        {
            return QString( "Sovereignty.xml" );
        };

        /*!
        return the filename of the Jumps.xml request
        */
        static const QString jumpsRequestID()
        {
            return QString( "Jumps.xml" );
        };

        /*!
        return the filename of the Kills.xml request
        */
        static const QString killsRequestID()
        {
            return QString( "Kills.xml" );
        };
};

#endif
