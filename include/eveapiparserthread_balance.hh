#ifndef __EVEAPIPARSERTHREAD_BALANCE_HH__
#define __EVEAPIPARSERTHREAD_BALANCE_HH__

#include <QDateTime>

#include <boost/shared_ptr.hpp>

#include "eveapiparserthread.hh"

using boost::shared_ptr;

class QDomDocument;
class QDomNode;

class EveApiDataBalance;

class EveApiParserThreadBalance: public EveApiParserThread
{
    Q_OBJECT
    public:
        /*!
        Construct the parser
        */
        EveApiParserThreadBalance( QObject* parent = 0 );

    protected:
        /*!
        Perform the actual parsing of the data, and emit a signal when done.
        The signal must be defined in the subclass
        */
        void doParse( const QString& parserId, const shared_ptr<QDomDocument> doc );

    private:
        /*!
        getTime
        */
        QDateTime apiDateTimeToQDateTime( QString& apiDateTime );

        /*!
        parse a "rowset" in the account balance data
        */
        void parseRowSet( QDomNode* rowset, shared_ptr<EveApiDataBalance>& data );

    signals:
        /*!
        This signal is emitted when parsing is complete
        */
        void parsingComplete( QString parserId, shared_ptr<EveApiDataBalance> parsedData );
};

#endif
