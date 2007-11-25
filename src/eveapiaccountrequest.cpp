#include "eveapiaccountrequest.hh"

/*!
pass the constructor args to the super-class
*/
EveApiAccountRequest::EveApiAccountRequest( const QString& requestType,
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
return a QStringList of filesystem directories,
relative to the data directory, in which to store cache
*/
QStringList EveApiAccountRequest::cachePath( const QString& scope,
        const QMap<QString, QString>& parameters )
{
    QStringList dirs;
    dirs << parameters.value( "userID" );
    dirs << scope;
    return dirs;
}

