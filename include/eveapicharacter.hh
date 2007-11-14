#ifndef __EVEAPICHARACTER_HH__
#define __EVEAPICHARACTER_HH__

#include <QObject>

class EveApiCharacter: public QObject
{
    Q_OBJECT
    public:
        EveApiCharacter( QObject* parent = 0 );
};

#endif
