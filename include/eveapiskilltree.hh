#ifndef __EVEAPISKILLTREE_HH__
#define __EVEAPISKILLTREE_HH__

#include "eveapirequest.hh"

class EveApiSkillTree: public EveApiRequest
{
    Q_OBJECT
    public:
        /*!
        pass the constructor args to the super-class
        */
        EveApiSkillTree( const QString& requestType, const QString& dataPath,
            const int& xmlIndent, QObject* parent = 0 );

    private:
        /*!
        Check the paramaters
        */
        bool validateParamaters( const QMap<QString, QString>& parameters, QUrl& url );

        /*!
        return a QStringList of filesystem directories,
        relative to the data directory, in which to store cache
        */
        QStringList cachePath( const QString& scope,
            const QMap<QString, QString>& parameters );
};

#endif
