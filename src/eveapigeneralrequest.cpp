#include "eveapigeneralrequest.hh"


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

