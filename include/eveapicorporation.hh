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

        /*!
        access the CorporationSheet api function
        */
        QString corporationSheet( QMap<QString, QString>& parameters );

        /*!
        access the StarbaseList api function
        */
        QString starbaseList( QMap<QString, QString>& parameters );

        /*!
        access the StarbaseDetail api function
        */
        QString starbaseDetail( QMap<QString, QString>& parameters );

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

        /*!
        return the filename of the CorporationSheet.xml request
        */
        static const QString corporationSheetRequestID()
        {
            return QString("CorporationSheet.xml");
        }

        /*!
        return the filename of the StarbaseList.xml request
        */
        static const QString starbaseListRequestID()
        {
            return QString("StarbaseList.xml");
        }

        /*!
        return the filename of the StarbaseDetail.xml request
        */
        static const QString starbaseDetailRequestID()
        {
            return QString("StarbaseDetail.xml");
        }
};

#endif
