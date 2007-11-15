#ifndef __EVEAPICHARACTER_HH__
#define __EVEAPICHARACTER_HH__

#include "eveapiscope.hh"

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

    private:
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
};

#endif
