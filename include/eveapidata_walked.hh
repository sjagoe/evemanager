#ifndef __EVEAPIDATA_WALKED_HH__
#define __EVEAPIDATA_WALKED_HH__
#if !defined(EVEAPI_NO_PARSING)

#include "eveapidata.hh"

class EveApiDataWalkedData: public QSharedData
{
    public:
        EveApiDataWalkedData();
        EveApiDataWalkedData( const EveApiDataWalkedData& other );
        ~EveApiDataWalkedData();
};

class EveApiDataWalked: public EveApiData
{
    public:
        EveApiDataWalked();

    private:
        QSharedDataPointer<EveApiDataWalkedData> _data;
};

#endif
#endif
