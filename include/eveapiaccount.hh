#ifndef __EVEAPIACCOUNT_HH__
#define __EVEAPIACCOUNT_HH__

#include "eveapiscope.hh"

class EveApiAccount: public EveApiScope
{
        Q_OBJECT
    public:
        /*!
        create the child classes that provide API functionality
        */
        EveApiAccount( QString& host,
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
        access the Characters api function
        */
        QString characters( QMap<QString, QString>& parameters );

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
        return the filename of the Characters.xml request
        */
        static const QString charactersRequestID()
        {
            return QString( "Characters.xml" );
        };
};

#endif
