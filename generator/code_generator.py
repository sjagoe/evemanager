import os.path
import string


HEADERS = "headers"
HEADER_EXT = "hh"
HEADER_DIR = "include"
SOURCES = "sources"
SOURCES_EXT = "cpp"
SOURCES_DIR = "src"
COMMON = "common"
OTHER = "other"
# HEADER_REQUEST_ID_BLOCK_TEMPLATE
#   1 api_function api method
#   2 method name
#   3 api_function api method
HEADER_REQUEST_ID_BLOCK_TEMPLATE = """
        /*!
        return the filename of the %(api_function)s request
        */
        static const QString %(method)sRequestID()
        {
            return QString( "%(api_function)s" );
        };
"""
# HEADER_ACCESS_BLOCK_TEMPLATE: 
#   1 api_function api method
#   2 Second param: method name
HEADER_ACCESS_BLOCK_TEMPLATE = """
        /*!
        access the %(api_function)s api function
        */
        QString %(method)s( QMap<QString, QString>& parameters );
"""
SOURCE_SETUP_BLOCK_TEMPLATE = """
    // %(api_function)s request
    requiredParams.clear();
    %(required)s
    optionalParams.clear();
    %(optional)s
    cacheID.clear();
    %(cacheID)s
    QString requestID = this->%(method)sRequestID();
    createRequest( requestID, requiredParams, optionalParams, cacheID,
                   proxyType, proxyHost, proxyPort, proxyUser, proxyPassword );
"""

SOURCE_ACCESS_BLOCK_TEMPLATE = """
/*!
access the %(api_function)s api function
*/
QString %(class_name)s::%(method)s( QMap<QString, QString>& parameters )
{
    QString id = this->%(method)sRequestID();
    return this->request( id, parameters );
}
"""

templates = {
    HEADERS: {
        COMMON: """
#ifndef %(define)s
#define %(define)s

#include <QMap>
#include <QString>
#include <QPair>

#include "%(inherit_file)s"


class %(class_name)s: public %(inherit)s
{
    public:
        %(class_name)s( QString& host,
                      QString& dataPath,
                      int& xmlIndent,
                      QString& scope,
                      const int& proxyType,
                      const QString& proxyHost,
                      const quint16& proxyPort,
                      const QString & proxyUser,
                      const QString & proxyPassword,
                      QObject* parent = 0 );
%(header_access_block)s
    protected:
        /*!
        Create request objects
        */
        void createRequest( QString& requestId,
                            QStringList& requiredParams,
                            QStringList& optionalParams,
                            QStringList& cacheId,
                            const int& p_type,
                            const QString& host,
                            const quint16& port,
                            const QString & user,
                            const QString & password );

    private:
        /*!
        create all requests (delegated from the constructor)
        */
        void createCommonRequests( const int& proxyType,
                                   const QString& proxyHost,
                                   const quint16& proxyPort,
                                   const QString & proxyUser,
                                   const QString & proxyPassword );
%(header_id_block)s
};


#endif

""", 
        OTHER: """
"""},
    SOURCES: {
        COMMON: """
#include "%(filename)s.hh"

#include "eveapicharacterrequest.hh"

/*!
create the child classes that provide API functionality
*/
%(class_name)s::%(class_name)s( QString& host,
                            QString& dataPath,
                            int& xmlIndent,
                            QString& scope,
                            const int& proxyType,
                            const QString& proxyHost,
                            const quint16& proxyPort,
                            const QString & proxyUser,
                            const QString & proxyPassword,
                            QObject* parent )
        : %(inherit)s( host, dataPath, xmlIndent, scope, parent )
{
    this->createCommonRequests( proxyType, proxyHost, proxyPort, proxyUser,
                                proxyPassword );
}

%(source_access_block)s

/*!
Create request objects
*/
void %(class_name)s::createRequest( QString& requestId,
                                  QStringList& requiredParams,
                                  QStringList& optionalParams,
                                  QStringList& cacheId,
                                  const int& p_type,
                                  const QString& host,
                                  const quint16& port,
                                  const QString & user,
                                  const QString & password )
{
    EveApiRequest* newRequest = new %(request_type)s( requestId,
            this->dataPath(),
            this->xmlIndent(),
            requiredParams,
            optionalParams,
            cacheId,
            p_type,
            host,
            port,
            user,
            password );
    this->addRequestType( requestId, newRequest );
}

void %(class_name)s::createCommonRequests( const int& proxyType,
        const QString & proxyHost,
        const quint16 & proxyPort,
        const QString & proxyUser,
        const QString & proxyPassword )
{
    QStringList requiredParams;
    QStringList optionalParams;
    QStringList cacheID;

%(source_setup_block)s
}

""",
        OTHER: """
"""}}


class Generator(object):

    def __init__(self):
        pass




if __name__ == "__main__":
    block_values = {
        "walletJournal": {
            "method": "walletJournal",
            "api_function": "WalletJournal.xml",
            "required": """requiredParams << "userID" << "characterID" << "apiKey";""",
            "optional": """optionalParams << "beforeRefID";""",
            "cacheID": """cacheID << "beforeRefID";""",
            "class_name": "EveApiCommon"},
        "accountBalance": {
            "method": "accountBalance",
            "api_function": "AccountBalance.xml",
            "required": """requiredParams << "userID" << "characterID" << "apiKey";""",
            "optional": "",
            "cacheID": "",
            "class_name": "EveApiCommon"},
        }
    class_values = {
        "class_name": "EveApiCommon",
        "inherit": "EveApiScope",
        "filename": "eveapicommon",
        "request_type": "EveApiCharacterRequest",
        }

    inherit_file = "%s.%s" % (class_values["inherit"].lower(), HEADER_EXT)
    define = "__%s_HH__" % class_values["class_name"].upper()
    class_values["define"] = define
    class_values["inherit_file"] = inherit_file

    header_id_blocks = ""
    header_access_blocks = ""
    source_setup_blocks = ""
    source_access_blocks = ""

    for blocks in block_values.itervalues():
        header_id_block = HEADER_REQUEST_ID_BLOCK_TEMPLATE % blocks
        header_id_blocks = header_id_blocks + header_id_block

        header_access_block = HEADER_ACCESS_BLOCK_TEMPLATE % blocks
        header_access_blocks = header_access_blocks + header_access_block

        source_setup_block = SOURCE_SETUP_BLOCK_TEMPLATE % blocks
        source_setup_blocks = source_setup_blocks + source_setup_block

        source_access_block = SOURCE_ACCESS_BLOCK_TEMPLATE % blocks
        source_access_blocks = source_access_blocks + source_access_block

    class_values["header_access_block"] = header_access_blocks
    class_values["header_id_block"] = header_id_blocks
    class_values["source_access_block"] = source_access_blocks
    class_values["source_setup_block"] = source_setup_blocks

    source = templates[SOURCES][COMMON] % class_values
    header = templates[HEADERS][COMMON] % class_values

    #print source
    #print header
