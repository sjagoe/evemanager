#include "eveapicharacterscope.hh"

/*!
pass the constructor args to the super-class
*/
EveApiCharacterScope::EveApiCharacterSheet( const QString& requestType,
    const QString& dataPath, const int& xmlIndent, QObject* parent )
        : EveApiRequest( requestType, dataPath, xmlIndent, parent )
{

}

/*!
Check the paramaters
*/
bool EveApiCharacterScope::validateParamaters( const QMap<QString, QString>& parameters, QUrl& url )
{
    QString userID = parameters.value("userID");
    QString charID = parameters.value("characterID");
    QString apiKey = parameters.value("apiKey");
    if (( userID.isNull() ) || ( charID.isNull() ) || ( apiKey.isNull() ))
    {
        return false;
    }
    url.addQueryItem("userID", userID);
    url.addQueryItem("characterID", charID);
    url.addQueryItem("apiKey", apiKey);
    return true;
}

/*!
return a QStringList of filesystem directories,
relative to the data directory, in which to store cache
*/
QStringList EveApiCharacterScope::cachePath( const QString& scope,
    const QMap<QString, QString>& parameters )
{
    QStringList dirs;
    dirs << parameters.value("userID");
    dirs << parameters.value("characterID");
    dirs << scope;
    return dirs;
}
