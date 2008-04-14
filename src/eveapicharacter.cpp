#include "eveapicharacter.hh"

#include <QList>
#include <QStringList>

/*!
create the child classes that provide API functionality
*/
EveApiCharacter::EveApiCharacter( QString& host,
                                  QString& dataPath,
                                  int& xmlIndent,
                                  QString& scope,
                                  const int& proxyType,
                                  const QString & proxyHost,
                                  const quint16 & proxyPort,
                                  const QString & proxyUser,
                                  const QString & proxyPassword,
                                  QObject* parent )
        : EveApiCommon( host, dataPath, xmlIndent, scope, proxyType, proxyHost,
                        proxyPort, proxyUser, proxyPassword, parent )
{
    this->createRequests( proxyType, proxyHost, proxyPort, proxyUser,
                          proxyPassword );
}

/*!
access the CharacterSheet api function
*/
QString EveApiCharacter::characterSheet( QMap<QString, QString>& parameters )
{
    QString id = this->characterSheetRequestID();
    return this->request( id, parameters );
}

/*!
access the SkillInTraining api function
*/
QString EveApiCharacter::skillInTraining( QMap<QString, QString>& parameters )
{
    QString id = this->skillInTrainingRequestID();
    return this->request( id, parameters );
}

/*!
create all requests (delegated from the constructor)
*/
void EveApiCharacter::createRequests( const int& proxyType,
                                      const QString & proxyHost,
                                      const quint16 & proxyPort,
                                      const QString & proxyUser,
                                      const QString & proxyPassword )
{
    QStringList requiredParams;
    QStringList optionalParams;
    QStringList cacheID;

    // CharacterSheet request
    requiredParams.clear();
    requiredParams << "userID" << "characterID" << "apiKey";
    optionalParams.clear();
    cacheID.clear();
    QString requestID = this->characterSheetRequestID();
    createRequest( requestID, requiredParams, optionalParams, cacheID,
                   proxyType, proxyHost, proxyPort, proxyUser, proxyPassword );

    // SkillInTraining request
    requiredParams.clear();
    requiredParams << "userID" << "characterID" << "apiKey";
    optionalParams.clear();
    cacheID.clear();
    requestID = this->skillInTrainingRequestID();
    createRequest( requestID, requiredParams, optionalParams, cacheID,
                   proxyType, proxyHost, proxyPort, proxyUser, proxyPassword );
}

