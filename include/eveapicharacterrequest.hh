#ifndef __EVEAPICHARACTERREQUEST_HH__
#define __EVEAPICHARACTERREQUEST_HH__

#include "eveapirequest.hh"

class EveApiCharacterRequest: public EveApiRequest
{
        Q_OBJECT
    public:
        /*!
        pass the constructor args to the super-class
        */
        EveApiCharacterRequest( const QString& requestType,
                                const QString& dataPath,
                                const int& xmlIndent,
                                const QList<QString>& requiredParams,
                                const QList<QString>& optionalParams,
                                const QList<QString>& fileIDParam,
                                const int& p_type,
                                const QString& host,
                                const quint16& port,
                                const QString & user,
                                const QString & password,
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
