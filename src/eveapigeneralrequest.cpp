#include "eveapigeneralrequest.hh"

//#include <iostream>

EveApiGeneralRequest::EveApiGeneralRequest( const QString& requestType,
        const QString& dataPath,
        const int& xmlIndent,
        const QList<QString>& requiredParams,
        const QList<QString>& optionalParams,
        const QList<QString>& fileIDParam,
        QObject* parent )
        : EveApiRequest( requestType, dataPath, xmlIndent, requiredParams, optionalParams, fileIDParam, parent )
{

}

// /*!
//Check the paramaters
//*/
//bool EveApiGeneralRequest::validateParamaters(
//    const QMap<QString, QString>& parameters, QUrl& url )
//{
//    QString userID = parameters.value( "userID" );
//    QString apiKey = parameters.value( "apiKey" );
//    if (( userID.isNull() ) || ( apiKey.isNull() ) )
//    {
//        return false;
//    }
//    url.addQueryItem( "userID", userID );
//    url.addQueryItem( "apiKey", apiKey );
//    return true;
//}

/*!
return a QStringList of filesystem directories, relative to the data directory, in which to store cache
*/
QStringList EveApiGeneralRequest::cachePath( const QString& scope,
        const QMap<QString, QString>& /*parameters*/ )
{
    QStringList dirs;
    dirs << scope;
    return dirs;
}

