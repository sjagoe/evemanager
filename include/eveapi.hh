#ifndef __EVEAPI_HH__
#define __EVEAPI_HH__

#include <QObject>

#include <QString>

#include "eveapieve.hh"
#include "eveapimap.hh"
#include "eveapicharacter.hh"
#include "eveapicorporation.hh"

class EveApi: public QObject
{
    Q_OBJECT
    public:
        /*!
        set up the scopes of the API
        */
        EveApi( QString& dataPath, QObject* parent = 0 );

        /*!
        provide access to areas of the api in the "/eve/" context
        */
        EveApiEve& eve();

        /*!
        provide access to areas of the api in the "/map/" context
        */
        EveApiMap& map();

        /*!
        provide access to aread of the api in the "/char/" context
        */
        EveApiCharacter& character();

        /*!
        provide access to aread of the api in the "/corp/" context
        */
        EveApiCorporation& corp();

    private:
        //! API Server hostname
        QString _hostName;

        //! path to the data subdirectory
        QString _dataPath;

        //! amount to indent XML blocks when writing files
        int _xmlIndent;

//    EveApiEve( QString& host, QString& dataPath, int& xmlIndent,
//            QString& scope, QObject* parent = 0 );

        //! "/eve/" scope
        EveApiEve* _eve;

        //! "/map/" scope
        EveApiMap* _map;

        //! "/char/" scope
        EveApiCharacter* _char;

        //! "/corp/" scope
        EveApiCorporation* _corp;

        /*!
        connect the signals of each scope member
        */
        void connectScope( EveApiScope* scope );

    signals:
        void requestComplete( QString id, QDomDocument result, QString httpResponse, QDateTime );
        void requestFailed( QString id, QString error, QString httpResponse );
};

#endif
