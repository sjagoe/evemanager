#ifndef __EVEAPIPARSERTHREAD_BALANCE_HH__
#define __EVEAPIPARSERTHREAD_BALANCE_HH__

#include "eveapiparserthread.hh"

#include "eveapidata_balance.hh"

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
        void doParse( const QString& parserId, const QDomDocument& doc );

    signals:
        /*!
        This signal is emitted when parsing is complete
        */
        void parsingComplete( QString parserId, EveApiDataBalance parsedData );
};

#endif
