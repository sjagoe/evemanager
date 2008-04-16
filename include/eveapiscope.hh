#ifndef __EVEAPISCOPE_HH__
#define __EVEAPISCOPE_HH__

#include <QObject>

#include <QMap>

#include <QString>

#include <QDateTime>

#include <QMutex>

#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

class QDomDocument;

class EveApiRequest;

class EveApiScope: public QObject
{
        Q_OBJECT
    public:
        /*!
        create the child classes that provide API functionality
        */
        EveApiScope( QString& host,
                     QString& dataPath,
                     int& xmlIndent,
                     QString& scope,
                     const int& proxyType,
                     const QString & proxyHost,
                     const quint16 & proxyPort,
                     const QString & proxyUser,
                     const QString & proxyPassword,
                     QObject* parent = 0 );

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
        QString request( QString& id, QMap<QString, QString>& parameters/*, bool internal = false, QString requestId = QString()*/ );

        /*!
        Create request objects
        */
        virtual void createRequest( QString& requestId,
                                    QStringList& requiredParams,
                                    QStringList& optionalParams,
                                    QStringList& cacheId,
                                    const int& p_type,
                                    const QString& host,
                                    const quint16& port,
                                    const QString & user,
                                    const QString & password ) = 0;

    private:
        //! QMutex to sync multiple access to the API
        QMutex _mutex;

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

        /*!
        create all requests (delegated from the constructor)
        */
        virtual void createRequests( const int& proxyType,
                                     const QString & proxyHost,
                                     const quint16 & proxyPort,
                                     const QString & proxyUser,
                                     const QString & proxyPassword ) = 0;

    signals:
        void requestComplete( QString id, shared_ptr<QDomDocument> result, QString httpResponse, QDateTime cacheTime );
        void requestFailed( QString id, QString error, QString httpResponse );
};

#endif
