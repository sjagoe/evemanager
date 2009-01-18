
/*
 * Copyright 2007-2008 Simon Jagoe
 *
 * This file is part of EVE_API_Qt.
 *
 * EVE_API_Qt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EVE_API_Qt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EVE_API_Qt.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "eveapiscope.hh"

#include "eveapirequest.hh"

#include <Qt>
#include <QMetaType>
#include <QDomDocument>

Q_DECLARE_METATYPE(shared_ptr<QDomDocument>);

/*!
  create the child classes that provide API functionality
*/
EveApi::Scope::Scope( QString& host,
                      QString& dataPath,
                      int& xmlIndent,
                      QString& scope,
                      const int& /*proxyType*/,
                      const QString & /*proxyHost*/,
                      const quint16 & /*proxyPort*/,
                      const QString & /*proxyUser*/,
                      const QString & /*proxyPassword*/,
                      QObject* parent )
    : QObject( parent )
{
    this->_hostName = host;
    this->_dataPath = dataPath;
    this->_xmlIndent = xmlIndent;
    this->_scope = scope;

    qRegisterMetaType<shared_ptr<QDomDocument> >("shared_ptr<QDomDocument>");
//    qRegisterMetaType<QDateTime>("QDateTime");
}

/*!
  Set the proxy to use for http requests
*/
void EveApi::Scope::setProxy( const int& proxyType,
                              const QString& proxyHost,
                              const quint16& proxyPort,
                              const QString & proxyUser,
                              const QString & proxyPassword )
{
    shared_ptr<EveApi::Request> request;
    foreach(request, this->_apiRequests)
    {
        request->setProxy(proxyType, proxyHost, proxyPort, proxyUser,
                          proxyPassword);
    }
}

/*!
  Get the host of the API server
*/
const QString& EveApi::Scope::hostName()
{
    return this->_hostName;
}

/*!
  Get the local data subdir
*/
const QString& EveApi::Scope::dataPath()
{
    return this->_dataPath;
}

/*!
  get the XML Indent amount
*/
const int& EveApi::Scope::xmlIndent()
{
    return this->_xmlIndent;
}

/*!
  get the current scope
*/
const QString& EveApi::Scope::scope()
{
    return this->_scope;
}

/*!
  Add a "Request Type" to the list
*/
void EveApi::Scope::addRequestType( 
    QString& id, shared_ptr<EveApi::Request> request )
{
    connect( request.get(),
             SIGNAL(requestComplete( QString, shared_ptr<QDomDocument>,
                                     QString, QDateTime, QString )),
             this, SIGNAL(requestComplete( QString, shared_ptr<QDomDocument>,
                                           QString, QDateTime, QString )),
             Qt::QueuedConnection );
    connect( request.get(),
             SIGNAL(requestFailed( QString, QString, QString )),
             this, SIGNAL(requestFailed( QString, QString, QString )),
             Qt::QueuedConnection );

    //    connect( request,
    //        SIGNAL(internalRequestComplete( QString, QDomDocument, QString, QDateTime )),
    //        this, SLOT(internalRequestComplete( QString, QDomDocument, QString, QDateTime )),
    //        Qt::QueuedConnection );
    //    connect( request,
    //        SIGNAL(internalRequestFailed( QString, QString, QString )),
    //        this, SIGNAL(internalRequestFailed( QString, QString, QString )),
    //        Qt::QueuedConnection );

    this->_apiRequests.insert( id, request );
}

/*!
  Call a request of the specified type
*/
QString EveApi::Scope::request(
    QString& id, QMap<QString, QString>& parameters
    /*, bool internal, QString requestId */)
{
    this->_mutex.lock();
    QString host = this->hostName();
    QString scopeStr = this->scope();
    shared_ptr<EveApi::Request> req = this->requestType( id );
    QString result;
    if (req)
    {
        result = req->addRequest( host, scopeStr, parameters/*, internal, requestId */);
    }
    this->_mutex.unlock();
    return result;
}

// /*!
//Call a request of the specified type (internal, i.e. use a different
//set of signals and slots. This allows the parser to create the api
//request isolated from pure xml requests.
//*/
//QString EveApi::Scope::internalRequest( QString& id, QMap<QString, QString>& parameters )
//{
//    this->_mutex.lock();
//    QString host = this->hostName();
//    QString scopeStr = this->scope();
//    EveApi::Request* req = this->requestType( id );
//    QString result;
//    if (req)
//    {
//        result = req->addInternalRequest( host, scopeStr, parameters );
//    }
//    this->_mutex.unlock();
//    return result;
//}

/*!
  return a previously added request type
*/
shared_ptr<EveApi::Request> EveApi::Scope::requestType( QString& id ) const
{
    return this->_apiRequests.value( id );
}
