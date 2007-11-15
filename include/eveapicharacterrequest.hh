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
        EveApiCharacterRequest( const QString& requestType, const QString& dataPath,
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
