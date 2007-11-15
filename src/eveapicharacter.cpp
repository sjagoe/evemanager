#include "eveapicharacter.hh"

#include "eveapicharacterrequest.hh"
#include "eveapiwalletjournalrequest.hh"

#include <QList>

/*!
create the child classes that provide API functionality
*/
EveApiCharacter::EveApiCharacter( QString& host, QString& dataPath, int& xmlIndent,
                                  QString& scope, QObject* parent )
        : EveApiScope( host, dataPath, xmlIndent, scope, parent )
{
    QList<QString> requiredParams;
    QList<QString> optionalParams;

    // CharacterSheet request
    requiredParams.clear();
    requiredParams.append( "userID" );
    requiredParams.append( "characterID" );
    requiredParams.append( "apiKey" );
    optionalParams.clear();
    QString requestID = this->characterSheetRequestID();
    EveApiRequest* newRequest = new EveApiCharacterRequest( requestID,
            this->dataPath(),
            this->xmlIndent(),
            requiredParams,
            optionalParams );
    this->addRequestType( requestID, newRequest );

    // SkillInTraining request
    requiredParams.clear();
    requiredParams.append( "userID" );
    requiredParams.append( "characterID" );
    requiredParams.append( "apiKey" );
    optionalParams.clear();
    requestID = this->skillInTrainingRequestID();
    newRequest = new EveApiCharacterRequest( requestID,
            this->dataPath(),
            this->xmlIndent(),
            requiredParams,
            optionalParams );
    this->addRequestType( requestID, newRequest );

    // AccountBalance request
    requiredParams.clear();
    requiredParams.append( "userID" );
    requiredParams.append( "characterID" );
    requiredParams.append( "apiKey" );
    optionalParams.clear();
    requestID = this->accountBalanceRequestID();
    newRequest = new EveApiCharacterRequest( requestID,
            this->dataPath(),
            this->xmlIndent(),
            requiredParams,
            optionalParams );
    this->addRequestType( requestID, newRequest );

    // WalletJournal request
    requiredParams.clear();
    requiredParams.append( "userID" );
    requiredParams.append( "characterID" );
    requiredParams.append( "apiKey" );
    optionalParams.clear();
    //optionalParams.append( "accountKey" );
    optionalParams.append( "beforeRefID" );
    requestID = this->walletJournalRequestID();
    newRequest = new EveApiCharacterRequest( requestID,
            this->dataPath(),
            this->xmlIndent(),
            requiredParams,
            optionalParams );
    this->addRequestType( requestID, newRequest );
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
access the AccountBalance api function
*/
QString EveApiCharacter::accountBalance( QMap<QString, QString>& parameters )
{
    QString id = this->accountBalanceRequestID();
    return this->request( id, parameters );
}

/*!
access the WalletJournal api function
*/
QString EveApiCharacter::walletJournal( QMap<QString, QString>& parameters )
{
    QString id = this->walletJournalRequestID();
    return this->request( id, parameters );
}
