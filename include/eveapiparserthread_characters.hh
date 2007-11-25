#ifndef __EVEAPIPARSERTHREAD_CHARACTERS_HH__
#define __EVEAPIPARSERTHREAD_CHARACTERS_HH__

#include <QDateTime>

#include <boost/shared_ptr.hpp>

#include "eveapiparserthread.hh"

using boost::shared_ptr;

class QDomDocument;
class QDomNode;

class EveApiDataCharacters;

class EveApiParserThreadCharacters: public EveApiParserThread
{
    Q_OBJECT
    public:
        /*!
        Construct the parser
        */
        EveApiParserThreadCharacters( QObject* parent = 0 );

    protected:
        /*!
        Perform the actual parsing of the data, and emit a signal when done.
        The signal must be defined in the subclass
        */
        void doParse( const QString& parserId, const shared_ptr<QDomDocument> doc );

    private:
        /*!
        parse a single character in the xml
        */
        void parseRowSet( QDomNode* rowset, shared_ptr<EveApiDataCharacters>& data );

    signals:
        /*!
        This signal is emitted when parsing is complete
        */
        void parsingComplete( QString parserId, shared_ptr<EveApiDataCharacters> parsedData );
};

#endif

