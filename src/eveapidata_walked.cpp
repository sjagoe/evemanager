#include "eveapidata_walked.hh"

EveApiDataWalkedData::EveApiDataWalkedData() :
    data()
{

}

EveApiDataWalkedData::EveApiDataWalkedData( const EveApiDataWalkedData& other ) :
    data()
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

const QList<QMap<QString, QString> >& EveApiDataWalked::data() const
{
    return this->_data->data;
}

void EveApiDataWalked::appendData( const QList<QMap<QString, QString> >& newData )
{
    this->_data->data = this->_data->data + newData;
}

void EveApiDataWalked::appendData( const QMap<QString, QString>& newData )
{
    this->_data->data.append( newData );
}
