#include "eveapireftypes.hh"

EveApiRefTypes::EveApiRefTypes( QString& requestType, QString& dataPath, int& xmlIndent, QObject* parent )
    : EveApiRequest( requestType, dataPath, xmlIndent, parent )
{

}

/*!
Check the paramaters
*/
bool EveApiRefTypes::validateParamaters(
    const QMap<QString, QString>& parameters, QUrl& url )
{

}

/*!
return a QStringList of filesystem directories, relative to the data directory, in which to store cache
*/
QStringList EveApiRefTypes::cachePath( QString& scope,
    const QPair<QString, QString>& characterID )
{
    QStringList dirs;
    dirs << scope;
    return dirs;
}

