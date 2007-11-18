#ifndef __EVEAPIDATA_HH__
#define __EVEAPIDATA_HH__

#include <QSharedData>
#include <QSharedDataPointer>

#include "eveapidatatype.hh"

class EveApiData
{
    public:
        EveApiData(){};
        EveApiData( ParsedDataType thisType ) :
            _type( thisType )
        { };

        inline const ParsedDataType& type()
        {
            return this->_type;
        }

    private:
        ParsedDataType _type;
};

#endif
