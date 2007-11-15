#include "eveapicharacter.hh"

#include "eveapicharacterscope.hh"
//#include "eveapiskillintraining.hh"

/*!
create the child classes that provide API functionality
*/
EveApiCharacter::EveApiCharacter( QString& host, QString& dataPath, int& xmlIndent,
    QString& scope, QObject* parent )
        : EveApiScope ( host, dataPath, xmlIndent, scope, parent )
{
    // CharacterSheet request
    QString requestID = this->characterSheetRequestID();
    EveApiRequest* newRequest = new EveApiCharacterScope(requestID,
        this->dataPath(), this->xmlIndent());
    this->addRequestType( requestID, newRequest );

    // SkillInTraining request
    requestID = this->skillInTrainingRequestID();
    newRequest = new EveApiCharacterScope(requestID,
        this->dataPath(), this->xmlIndent());
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
