#ifndef __EVEAPICHARACTER_HH__
#define __EVEAPICHARACTER_HH__

#include "eveapicommon.hh"

class EveApiCharacter: public EveApiCommon
{
        Q_OBJECT
    public:
        /*!
        create the child classes that provide API functionality
        */
        EveApiCharacter( QString& host,
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
        access the CharacterSheet api function
        */
        QString characterSheet( QMap<QString, QString>& parameters );

        /*!
        access the SkillInTraining api function
        */
        QString skillInTraining( QMap<QString, QString>& parameters );

    private:
        /*!
        create all requests (delegated from the constructor)
        */
        void createRequests( const int& proxyType,
                             const QString & proxyHost,
                             const quint16 & proxyPort,
                             const QString & proxyUser,
                             const QString & proxyPassword );

    private:
        /*!
        return the filename of the Sovereignty.xml request
        */
        static const QString characterSheetRequestID()
        {
            return QString( "CharacterSheet.xml" );
        };

        /*!
        return the filename of the SkillInTraining.xml request
        */
        static const QString skillInTrainingRequestID()
        {
            return QString( "SkillInTraining.xml" );
        };
};

#endif
