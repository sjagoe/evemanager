#include "eveapidata_walked.hh"

EveApiDataWalkedData::EveApiDataWalkedData()
{

}

EveApiDataWalkedData::EveApiDataWalkedData( const EveApiDataWalkedData& other )
{

}

EveApiDataWalkedData::~EveApiDataWalkedData()
{

}

EveApiDataWalked::EveApiDataWalked() :
    EveApiData( PDT_WALKED )
{
    this->_data = new EveApiDataWalkedData;
}
