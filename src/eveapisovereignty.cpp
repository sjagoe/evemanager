#include "eveapisovereignty.hh"

/*!
pass the constructor args to the super-class
*/
EveApiSovereignty::EveApiSovereignty( const QString& requestType,
    const QString& dataPath, const int& xmlIndent, QObject* parent )
        : EveApiRequest( requestType, dataPath, xmlIndent, parent )
{

}

/*!
Check the paramaters
*/
bool EveApiSovereignty::validateParamaters( const QMap<QString, QString>& parameters, QUrl& url )
{
    QString userID = parameters.value("userID");
    QString apiKey = parameters.value("apiKey");
    if (( userID.isNull() ) || ( apiKey.isNull() ))
    {
        return false;
    }
    url.addQueryItem("userID", userID);
    url.addQueryItem("apiKey", apiKey);
    return true;
}

/*!
return a QStringList of filesystem directories,
relative to the data directory, in which to store cache
*/
QStringList EveApiSovereignty::cachePath( const QString& scope,
    const QMap<QString, QString>& parameters )
{
    QStringList dirs;
    dirs << scope;
    return dirs;
}
