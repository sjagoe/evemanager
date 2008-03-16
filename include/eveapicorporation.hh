#ifndef __EVEAPICORPORATION_HH__
#define __EVEAPICORPORATION_HH__

#include "eveapicommon.hh"

class EveApiCorporation: public EveApiCommon
{
    Q_OBJECT
    public:
        /*!
        create the child classes that provide API functionality
        */
        EveApiCorporation( QString& host, QString& dataPath, int& xmlIndent,
            QString& scope, QObject* parent = 0 );

        /*!
        access the MemberTracking api function
        */
        QString memberTracking( QMap<QString, QString>& parameters );

    private:
        /*!
        create all requests (delegated from the constructor)
        */
        void createRequests();

        /*!
        return the filename of the MemberTracking.xml request
        */
        static const QString memberTrackingRequestID()
        {
            return QString("MemberTracking.xml");
        }
};

#endif
