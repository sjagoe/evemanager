#ifndef __EVEAPIREFTYPE_HH__
#define __EVEAPIREFTYPE_HH__

#include "eveapirequest.hh"

class EveApiRefTypes: public EveApiRequest
{
    Q_OBJECT
    public:
        EveApiRefTypes( QString& dataPath, int& xmlIndent, QObject* parent = 0 );

    private:
        /*!
        Check the paramaters
        */
        bool validateParamaters( const QMap<QString, QString>& parameters, QUrl& url );

        /*!
        return a QStringList of filesystem directories, relative to the data directory, in which to store cache
        */
        QStringList cachePath( QString& scope, const QPair<QString, QString>& characterID );
};

#endif
