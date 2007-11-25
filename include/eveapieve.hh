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

        /*!
        access the AllianceList api function
        */
        QString allianceList( QMap<QString, QString>& parameters );

//    protected slots:
//        /*!
//        This slot is called when an internal request is complete, so that it
//        can be parsed
//        */
//        void internalRequestComplete( QString id, QDomDocument result, QString httpResponse, QDateTime cacheTime ){};

    private:
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

        /*!
        return the filnename of the AllianceList.xml request
        */
        static const QString allianceListRequestID()
        {
            return QString("AllianceList.xml");
        };
};

#endif
