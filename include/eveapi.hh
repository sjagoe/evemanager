#ifndef __EVEAPI_HH__
#define __EVEAPI_HH__

#include <QObject>

#include <QString>

#include "eveapieve.hh"
#include "eveapimap.hh"

class EveApi: public QObject
{
    Q_OBJECT
    public:
        /*!
        set up the scopes of the API
        */
        EveApi( QObject* parent = 0 );

        /*!
        provide access to areas of the api in the "/eve/" context
        */
        EveApiEve* eve();

        /*!
        provide access to areas of the api in the "/map/" context
        */
        EveApiMap* map();

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

    signals:
        void requestComplete( QString id, QDomDocument result, QString httpResponse );
        void requestFailed( QString id, QString error, QString httpResponse );
};

#endif
