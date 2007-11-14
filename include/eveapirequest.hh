#ifndef __EVEAPIREQUEST_HH__
#define __EVEAPIREQUEST_HH__

#include <QObject>

//#include <QHttp>
#include <QHttpResponseHeader>
#include <QMap>
#include <QPair>
#include <QString>
#include <QDomDocument>
#include <QString>
#include <QUrl>
#include <QStringList>

class QHttp;
class QBuffer;

class EveApiRequest: public QObject
{
    Q_OBJECT
    public:
        /*!
        Contructor, calls super-class constructor, creates dynamic objects
        */
        EveApiRequest( QString& requestType, QString& dataPath, int& xmlIndent, QObject* parent = 0 );

        /*!
        Add a request to be handled.

        \return unique request identifier (used to id a completed request)
        */
        QString addRequest( QString& host, QString& scope,
            QMap<QString, QString>& parameters );

    protected:
        /*!
        return the file extension (.aspx)
        */
        static const char* fileExtension()
        {
            return ".aspx";
        };

        /*!
        return the server path (URI) to access the requested information
        */
        QString path( const QString& scope );

        /*!
        return the requestType
        */
        const QString& requestType() const;

        /*!
        make a unique string ID
        */
        QString makeID( const QString& scope, int& id );

    private:
        //! amount to indent blocks of XML
        int _xmlIndent;

        //! currently active request
        int _currentRequest;

        //! Filename on the server (excluding ".aspx")
        QString _requestType;

        //! local sub-directory in which to cache data
        QString _dataPath;

        //! HTTP object that performs requests to the EVE API
        QHttp* _http;

        //! QMap mapping request IDs to buffers
        QMap<int, QPair<QBuffer*, QBuffer*> > _requestBuffers;

        //! QMap mapping IDs to readable requests
        QMap<int, QPair<QString, QString> > _requests;

        //! QMap mapping http id to a unique QString ID
        QMap<int, QString> _id;

        //! QMap of the request and HTTP response
        QMap<int, QString> _response;

        //! QMap of character identifiers
        QMap<int, QPair<QString, QString> > _characterID;

        /*!
        Check the paramaters
        */
        virtual bool validateParamaters( const QMap<QString, QString>& parameters, QUrl& url ) = 0;

        /*!
        return a QStringList of filesystem directories, relative to the data directory, in which to store cache
        */
        virtual QStringList cachePath( const QPair<QString, QString>& characterID ) = 0;

    private slots:
        /*!
        signal that a request has begun
        */
        void requestStarted( int id );

        /*!
        signal that a request has finished so that the result can be delivered
        */
        void requestFinished( int id, bool error );

        /*!
        An http response is received
        */
        void responseHeaderReceived( QHttpResponseHeader head );

    signals:
        void requestComplete( QString id, QDomDocument result, QString httpResponse );
        void requestFailed( QString id, QString error, QString httpResponse );
};



#endif
