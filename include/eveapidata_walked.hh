#ifndef __EVEAPIDATA_WALKED_HH__
#define __EVEAPIDATA_WALKED_HH__

#include <QList>
#include <QMap>
#include <QString>

#include "eveapidata.hh"

class EveApiDataWalkedData: public QSharedData
{
    public:
        EveApiDataWalkedData();
        EveApiDataWalkedData( const EveApiDataWalkedData& other );
        ~EveApiDataWalkedData();

        QList<QMap<QString, QString> > data;
};

class EveApiDataWalked: public EveApiData
{
    public:
        EveApiDataWalked();

        const QList<QMap<QString, QString> >& data() const;

        void appendData( const QList<QMap<QString, QString> >& newData );

        void appendData( const QMap<QString, QString>& newData );

    private:
        QSharedDataPointer<EveApiDataWalkedData> _data;
};

#endif
