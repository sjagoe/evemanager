#include "eveapidata_characters.hh"

/*!
Construct a character
*/
EveApiDataCharacter::EveApiDataCharacter( QString& name, QString& corpName,
        QString& charId, QString& corpId ) :
        _name( name ),
        _corpName( corpName ),
        _charId( charId ),
        _corpId( corpId )
{

}

/*!
return the charName
*/
const QString& EveApiDataCharacter::name()
{
    return this->_name;
}

/*!
return the corp name
*/
const QString& EveApiDataCharacter::corpName()
{
    return this->_corpName;
}

/*!
return the charId
*/
const QString& EveApiDataCharacter::charId()
{
    return this->_charId;
}

/*!
return the corpId
*/
const QString& EveApiDataCharacter::corpId()
{
    return this->_corpId;
}

/*!
construct the data container for account balance
*/
EveApiDataCharacters::EveApiDataCharacters() :
        EveApiData( PDT_CHARACTERLIST )
{

}

/*!
Add character
*/
void EveApiDataCharacters::addCharacter( QString& name, QString& corpName,
        QString& charId,
        QString& corpId )
{
    EveApiDataCharacter newChar( name, corpName, charId, corpId );

    this->_characters.append( newChar );
}

/*!
get all characters
*/
const QList<EveApiDataCharacter>& EveApiDataCharacters::getCharacters()
{
    return this->_characters;
}
