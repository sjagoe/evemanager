#ifndef __EVEAPIMAP_HH__
#define __EVEAPIMAP_HH__

#include "eveapiscope.hh"

class EveApiMap: public EveApiScope
{
    Q_OBJECT
    public:
        /*!
        create the child classes that provide API functionality
        */
        EveApiMap( QString& host, QString& dataPath, int& xmlIndent,
            QString& scope, QObject* parent = 0 );

        /*!
        access the Sovereignty api function
        */
        QString sovereignty( QMap<QString, QString>& parameters );

    protected slots:
        /*!
        This slot is called when an internal request is complete, so that it
        can be parsed
        */
        void internalRequestComplete( QString id, QDomDocument result, QString httpResponse, QDateTime cacheTime ){};

    private:
        /*!
        return the filename of the Sovereignty.xml request
        */
        static const QString sovereigntyRequestID()
        {
            return QString("Sovereignty.xml");
        };
};

#endif
