#include "eveapigeneralrequest.hh"


EveApiGeneralRequest::EveApiGeneralRequest( const QString& requestType,
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

