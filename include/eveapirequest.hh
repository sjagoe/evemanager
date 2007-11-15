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
#include <QDateTime>

class QHttp;
class QBuffer;

class EveApiRequest: public QObject
{
    Q_OBJECT
    public:
        /*!
        Contructor, calls super-class constructor, creates dynamic objects
        */
        EveApiRequest( const QString& requestType, const QString& dataPath,
            const int& xmlIndent, QObject* parent = 0 );

        virtual ~EveApiRequest() {};

        /*!
        Add a request to be handled.

        \return unique request identifier (used to id a completed request)
        */
        QString addRequest( const QString& host, const QString& scope,
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
        QMap<int, QBuffer* > _requestBuffers;

        //! QMap mapping IDs to readable requests (QPair<scope, file>)
        QMap<int, QPair<QString, QString> > _requests;

        //! QMap mapping http id to a unique QString ID
        QMap<int, QString> _id;

        //! QMap of the request and HTTP response
        QMap<int, QString> _response;

        //! QMap of character identifiers
        QMap<int, QMap<QString, QString> > _paramaters;

        /*!
        Check the paramaters
        */
        virtual bool validateParamaters( const QMap<QString, QString>& parameters, QUrl& url ) = 0;

        /*!
        return a QStringList of filesystem directories, relative to the data directory, in which to store cache
        */
        virtual QStringList cachePath( const QString& scope,
            const QMap<QString, QString>& parameters ) = 0;

        /*!
        Fetch from API
        */
        QString fetchFromApi( const QString& host, const QString& scope,
            const QMap<QString, QString>& parameters );

        /*!
        Get the time that the cache expires from a QDomDocument
        */
        QDateTime getCacheTime( const QDomDocument& xmlDocument );

        /*!
        convert a time specified in the API XML output to a QDateTime
        */
        QDateTime eveApiTimeToQDateTime( QString timeString );

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
