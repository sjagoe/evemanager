import os.path
import string

import lxml.etree

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
    requestID = this->%(method)sRequestID();
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
#ifndef %(define)s
#define %(define)s

#include "%(inherit_file)s"

class %(class_name)s: public %(inherit)s
{
        Q_OBJECT
    public:
        /*!
        create the child classes that provide API functionality
        */
        %(class_name)s( QString& host,
                       QString& dataPath,
                       int& xmlIndent,
                       QString& scope,
                       const int& proxyType,
                       const QString & proxyHost,
                       const quint16 & proxyPort,
                       const QString & proxyUser,
                       const QString & proxyPassword,
                       QObject* parent = 0 );

%(header_access_block)s

    private:
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

        /*!
        create all requests (delegated from the constructor)
        */
        void createRequests( const int& proxyType,
                             const QString & proxyHost,
                             const quint16 & proxyPort,
                             const QString & proxyUser,
                             const QString & proxyPassword );
%(header_id_block)s
};

#endif

"""},
    SOURCES: {
        COMMON: """
#include "%(filename)s.hh"

#include "%(request_type_include)s"

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
    QString requestID;

%(source_setup_block)s
}

""",
        OTHER: """
#include "%(filename)s.hh"

#include "%(request_type_include)s"

/*!
create the child classes that provide API functionality
*/
%(class_name)s::%(class_name)s( QString& host,
                              QString& dataPath,
                              int& xmlIndent,
                              QString& scope,
                              const int& proxyType,
                              const QString & proxyHost,
                              const quint16 & proxyPort,
                              const QString & proxyUser,
                              const QString & proxyPassword,
                              QObject* parent ) :
        %(inherit)s( host, dataPath, xmlIndent, scope, parent )
{
    this->createRequests( proxyType, proxyHost, proxyPort, proxyUser,
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

/*!
create all requests (delegated from the constructor)
*/
void %(class_name)s::createRequests( const int& proxyType,
                                    const QString & proxyHost,
                                    const quint16 & proxyPort,
                                    const QString & proxyUser,
                                    const QString & proxyPassword )
{
    QStringList requiredParams;
    QStringList optionalParams;
    QStringList cacheID;
    QString requestID;

%(source_setup_block)s
}

"""}}


class Generator(object):

    def __init__(self):
        pass

class Parser(object):

    def __init__(self):
        self._class_name = "class_name"
        self._class_values = ["template",
                              self._class_name,
                              "inherit",
                              "filename",
                              "request_type",
                              ]

    def _parse_class_values(self, scope):
        values = {}
        #values["template"] = scope.xpath("template").text
        for item in self._class_values:
            values[item] = scope.xpath(item)[0].text.strip()
        return values

    def _parse_params(self, params, param_base):
        param_string = ""
        if len(params) > 0:                
            param_string = param_base
            for r in params:
                param_string = "%s << \"%s\"" % (param_string, r.text.strip())
            param_string = param_string + ";"
        return param_string

    def _parse_block_values(self, methods, class_name):
        values = {}
        for method in methods:
            method_values = {self._class_name: class_name}
            name = method.get("name")
            method_values["method"] = name
            method_values["api_function"] = \
                method.xpath("api_function")[0].text.strip()
            required_params = self._parse_params(
                method.xpath("params/required"), "requiredParams")
            optional_params = self._parse_params(
                method.xpath("params/optional"), "optionalParams")
            cacheID_params = self._parse_params(
                method.xpath("params/cacheID"), "cacheID")
            method_values["required"] = required_params
            method_values["optional"] = optional_params
            method_values["cacheID"] = cacheID_params
            values[name] = method_values
        return values

    def _parse_values(self, xml):
        class_values = {}
        block_values = {}
        scopes = xml.xpath("/eveapi_code_generator/scopes/scope")
        for scope in scopes:
            name = scope.get("name")
            c_values = self._parse_class_values(scope)
            b_values = self._parse_block_values(scope.xpath("methods/method"),
                                           c_values[self._class_name])
            class_values[name] = c_values
            block_values[name] = b_values
        return (class_values, block_values)

    def parse(self, filename):
        fh = open(filename)
        xml = lxml.etree.parse(fh)
        fh.close()

        class_values, block_values = self._parse_values(xml)

        return (class_values, block_values)

if __name__ == "__main__":
    p = Parser()
    class_values, block_values = p.parse("generator.xml")

    for scope_name, class_value in class_values.iteritems():
        block_value = block_values[scope_name]

        inherit_file = "%s.%s" % (class_value["inherit"].lower(), HEADER_EXT)
        define = "__%s_HH__" % class_value["class_name"].upper()
        request_type_include = "%s.%s" % (class_value["request_type"].lower(),
                                          HEADER_EXT)
        class_value["define"] = define
        class_value["inherit_file"] = inherit_file
        class_value["request_type_include"] = request_type_include

        header_id_blocks = ""
        header_access_blocks = ""
        source_setup_blocks = ""
        source_access_blocks = ""

        for blocks in block_value.itervalues():
            header_id_block = HEADER_REQUEST_ID_BLOCK_TEMPLATE % blocks
            header_id_blocks = header_id_blocks + header_id_block

            header_access_block = HEADER_ACCESS_BLOCK_TEMPLATE % blocks
            header_access_blocks = header_access_blocks + header_access_block

            source_setup_block = SOURCE_SETUP_BLOCK_TEMPLATE % blocks
            source_setup_blocks = source_setup_blocks + source_setup_block

            source_access_block = SOURCE_ACCESS_BLOCK_TEMPLATE % blocks
            source_access_blocks = source_access_blocks + source_access_block

        class_value["header_access_block"] = header_access_blocks
        class_value["header_id_block"] = header_id_blocks
        class_value["source_access_block"] = source_access_blocks
        class_value["source_setup_block"] = source_setup_blocks

        source = templates[SOURCES][class_value["template"]] % class_value
        header = templates[HEADERS][class_value["template"]] % class_value
        
        header_file = "%s.%s" % (class_value["filename"].lower(), HEADER_EXT)
        source_file = "%s.%s" % (class_value["filename"].lower(), SOURCES_EXT)

        header_fh = open(header_file, "w")
        header_fh.write(header)
        header_fh.close()

        source_fh = open(source_file, "w")
        source_fh.write(source)
        source_fh.close()


#     block_values = {
#         "walletJournal": {
#             "method": "walletJournal",
#             "api_function": "WalletJournal.xml",
#             "required": """requiredParams << "userID" << "characterID" << "apiKey";""",
#             "optional": """optionalParams << "beforeRefID";""",
#             "cacheID": """cacheID << "beforeRefID";""",
#             "class_name": "EveApiCommon"},
#         "accountBalance": {
#             "method": "accountBalance",
#             "api_function": "AccountBalance.xml",
#             "required": """requiredParams << "userID" << "characterID" << "apiKey";""",
#             "optional": "",
#             "cacheID": "",
#             "class_name": "EveApiCommon"},
#         }
#     class_values = {
#         "class_name": "EveApiCommon",
#         "inherit": "EveApiScope",
#         "filename": "eveapicommon",
#         "request_type": "EveApiCharacterRequest",
#         }

#     inherit_file = "%s.%s" % (class_values["inherit"].lower(), HEADER_EXT)
#     define = "__%s_HH__" % class_values["class_name"].upper()
#     class_values["define"] = define
#     class_values["inherit_file"] = inherit_file

#     header_id_blocks = ""
#     header_access_blocks = ""
#     source_setup_blocks = ""
#     source_access_blocks = ""

#     for blocks in block_values.itervalues():
#         header_id_block = HEADER_REQUEST_ID_BLOCK_TEMPLATE % blocks
#         header_id_blocks = header_id_blocks + header_id_block

#         header_access_block = HEADER_ACCESS_BLOCK_TEMPLATE % blocks
#         header_access_blocks = header_access_blocks + header_access_block

#         source_setup_block = SOURCE_SETUP_BLOCK_TEMPLATE % blocks
#         source_setup_blocks = source_setup_blocks + source_setup_block

#         source_access_block = SOURCE_ACCESS_BLOCK_TEMPLATE % blocks
#         source_access_blocks = source_access_blocks + source_access_block

#     class_values["header_access_block"] = header_access_blocks
#     class_values["header_id_block"] = header_id_blocks
#     class_values["source_access_block"] = source_access_blocks
#     class_values["source_setup_block"] = source_setup_blocks

#     source = templates[SOURCES][COMMON] % class_values
#     header = templates[HEADERS][COMMON] % class_values

#     #print source
#     #print header

