#ifndef __EVEAPIEVE_HH__
#define __EVEAPIEVE_HH__

#include "eveapiscope.hh"

class EveApiEve: public EveApiScope
{
        Q_OBJECT
    public:
        /*!
        create the child classes that provide API functionality
        */
        EveApiEve( QString& host,
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
        access the RefTypes api function
        */
        QString refTypes( QMap<QString, QString>& parameters );

        /*!
        access the SkillTree api function
        */
        QString skillTree( QMap<QString, QString>& parameters );

        /*!
        access the AllianceList api function
        */
        QString allianceList( QMap<QString, QString>& parameters );

        /*!
        access the ErrorList api function
        */
        QString errorList( QMap<QString, QString>& parameters );

        /*!
        access the CharacterID api function
        */
        QString characterID( QMap<QString, QString>& parameters );

        /*!
        access the ConquerableStationsList api function
        */
        QString conquerableStationsList( QMap<QString, QString>& parameters );

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
        return the filename of the RefType.xml request
        */
        static const QString refTypesRequestID()
        {
            return QString( "RefTypes.xml" );
        };

        /*!
        return the filnename of the SkillTree.xml request
        */
        static const QString skillTreeRequestID()
        {
            return QString( "SkillTree.xml" );
        };

        /*!
        return the filnename of the AllianceList.xml request
        */
        static const QString allianceListRequestID()
        {
            return QString( "AllianceList.xml" );
        };

        /*!
        return the filnename of the ErrorList.xml request
        */
        static const QString errorListRequestID()
        {
            return QString( "ErrorList.xml" );
        };

        /*!
        return the filnename of the CharacterID.xml request
        */
        static const QString characterIDRequestID()
        {
            return QString( "CharacterID.xml" );
        };

        /*!
        return the filnename of the ConquerableStationsList.xml request
        */
        static const QString conquerableStationsListRequestID()
        {
            return QString( "ConquerableStationsList.xml" );
        };
};

#endif
