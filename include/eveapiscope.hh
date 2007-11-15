#ifndef __EVEAPISCOPE_HH__
#define __EVEAPISCOPE_HH__

#include <QObject>

#include <QMap>

#include <QString>

#include <QDomDocument>

class EveApiRequest;

class EveApiScope: public QObject
{
    Q_OBJECT
    public:
        /*!
        create the child classes that provide API functionality
        */
        EveApiScope( QString& host, QString& dataPath, int& xmlIndent,
            QString& scope, QObject* parent = 0 );

        virtual ~EveApiScope() {};

    protected:
        /*!
        Get the host of the API server
        */
        const QString& hostName();

        /*!
        Get the local data subdir
        */
        const QString& dataPath();

        /*!
        get the XML Indent amount
        */
        const int& xmlIndent();

        /*!
        get the current scope
        */
        const QString& scope();

        /*!
        Add a "Request Type" to the list
        */
        void addRequestType( QString& id, EveApiRequest* request );

        /*!
        Call a request of the specified type
        */
        QString request( QString& id, QMap<QString, QString>& parameters );

    private:
        //! The API host server
        QString _hostName;

        //! The subdirectory in which to store cache
        QString _dataPath;

        //! amount to indent XML files when saved
        int _xmlIndent;

        //! Scope (i.e. server directory)
        QString _scope;

        //! QMap storing each of the possible requests in this scope
        QMap<QString, EveApiRequest*> _apiRequests;

        /*!
        return a previously added request type
        */
        EveApiRequest* requestType( QString& id ) const;

    signals:
        void requestComplete( QString id, QDomDocument result, QString httpResponse );
        void requestFailed( QString id, QString error, QString httpResponse );

};

#endif
