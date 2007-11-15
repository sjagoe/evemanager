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
        EveApiEve( QString& host, QString& dataPath, int& xmlIndent,
            QString& scope, QObject* parent = 0 );

        /*!
        access the RefTypes api function
        */
        QString refTypes( QMap<QString, QString>& parameters );

        /*!
        access the SkillTree api function
        */
        QString skillTree( QMap<QString, QString>& parameters );

    private:
        /*!
        return the filename of the RefType.xml request
        */
        static const QString refTypesRequestID()
        {
            return QString("RefTypes.xml");
        };

        /*!
        return the filnename of the SkillTree.xml request
        */
        static const QString skillTreeRequestID()
        {
            return QString("SkillTree.xml");
        };
};

#endif
