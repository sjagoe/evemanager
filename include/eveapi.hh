#ifndef __EVEAPI_HH__
#define __EVEAPI_HH__

#include <QObject>

#include <QString>

#include <boost/shared_ptr.hpp>

#include "eveapiaccount.hh"
#include "eveapieve.hh"
#include "eveapimap.hh"
#include "eveapicharacter.hh"
#include "eveapicorporation.hh"

using boost::shared_ptr;

class QDomDocument;

class EveApi: public QObject
{
        Q_OBJECT
    public:
        /*!
        set up the scopes of the API
        */
        EveApi( QString& dataPath,
                const int& proxyType = 0,
                const QString& proxyHost = QString(),
                const quint16& proxyPort = 0,
                const QString & proxyUser = QString(),
                const QString & proxyPassword = QString(),
                QObject* parent = 0 );

        /*!
        provide access to areas of the api in the "/account/" context
        */
        EveApiAccount& account();

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

        //! "/eve/" scope
        EveApiEve* _eve;

        //! "/map/" scope
        EveApiMap* _map;

        //! "/char/" scope
        EveApiCharacter* _char;

        //! "/corp/" scope
        EveApiCorporation* _corp;

        EveApiAccount* _account;

        /*!
        create the scopes, and connect scope-specific signals and slots
        */
        void createScopes( const int& p_type,
                           const QString& host,
                           const quint16& port,
                           const QString & user,
                           const QString & password );

        /*!
        connect the signals of each scope member
        */
        void connectScope( EveApiScope* scope );

    signals:
        void requestComplete( QString id, shared_ptr<QDomDocument> result, QString httpResponse, QDateTime );
        void requestFailed( QString id, QString error, QString httpResponse );
};

#endif
