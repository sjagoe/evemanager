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
