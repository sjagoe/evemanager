
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

#include "eveapicharacterrequest.hh"

/*!
pass the constructor args to the super-class
*/
EveApiCharacterRequest::EveApiCharacterRequest( const QString& requestType,
        const QString& dataPath,
        const int& xmlIndent,
        const QList<QString>& requiredParams,
        const QList<QString>& optionalParams,
        const QList<QString>& fileIDParam,
        const int& p_type,
        const QString & host,
        const quint16 & port,
        const QString & user,
        const QString & password,
        QObject* parent )
        : EveApiRequest( requestType, dataPath, xmlIndent, requiredParams,
                         optionalParams, fileIDParam, p_type, host, port, user,
                         password, parent )
{

}

// /*!
//Check the paramaters
//*/
//bool EveApiCharacterRequest::validateParamaters( const QMap<QString, QString>& parameters, QUrl& url )
//{
//    QString userID = parameters.value( "userID" );
//    QString charID = parameters.value( "characterID" );
//    QString apiKey = parameters.value( "apiKey" );
//    if (( userID.isNull() ) || ( charID.isNull() ) || ( apiKey.isNull() ) )
//    {
//        return false;
//    }
//    url.addQueryItem( "userID", userID );
//    url.addQueryItem( "characterID", charID );
//    url.addQueryItem( "apiKey", apiKey );
//    return true;
//}

/*!
return a QStringList of filesystem directories,
relative to the data directory, in which to store cache
*/
QStringList EveApiCharacterRequest::cachePath( const QString& scope,
        const QMap<QString, QString>& parameters )
{
    QStringList dirs;
    dirs << parameters.value( "userID" );
    dirs << parameters.value( "characterID" );
    dirs << scope;
    return dirs;
}
