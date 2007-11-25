#ifndef __EVEAPIACCOUNTREQUEST_HH__
#define __EVEAPIACCOUNTREQUEST_HH__

#include "eveapirequest.hh"

class EveApiAccountRequest: public EveApiRequest
{
        Q_OBJECT
    public:
        /*!
        pass the constructor args to the super-class
        */
        EveApiAccountRequest( const QString& requestType,
                                const QString& dataPath,
                                const int& xmlIndent,
                                const QList<QString>& requiredParams,
                                const QList<QString>& optionalParams,
                                const QList<QString>& fileIDParam,
                                QObject* parent = 0 );

    private:
        /*!
        return a QStringList of filesystem directories,
        relative to the data directory, in which to store cache
        */
        QStringList cachePath( const QString& scope,
                               const QMap<QString, QString>& parameters );
};

#endif
