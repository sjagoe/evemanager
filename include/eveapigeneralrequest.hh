#ifndef __EVEAPIGENERALREQUEST_HH__
#define __EVEAPIGENERALREQUEST_HH__

#include "eveapirequest.hh"

class EveApiGeneralRequest: public EveApiRequest
{
        Q_OBJECT
    public:
        /*!
        pass the constructor args to the super-class
        */
        EveApiGeneralRequest( const QString& requestType,
                              const QString& dataPath,
                              const int& xmlIndent,
                              const QList<QString>& requiredParams,
                              const QList<QString>& optionalParams,
                              const QList<QString>& fileIDParam,
                              QObject* parent = 0 );

    private:
        /*!
        return a QStringList of filesystem directories, relative to the data directory, in which to store cache
        */
        QStringList cachePath( const QString& scope,
                               const QMap<QString, QString>& parameters );
};

#endif
