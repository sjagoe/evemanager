#ifndef __EVEAPIDATA_CHARACTERS_HH__
#define __EVEAPIDATA_CHARACTERS_HH__

#include "eveapidatatable.hh"

#include <QList>
#include <QString>

class EveApiDataCharacter
{
    public:
        /*!
        Construct a character
        */
        EveApiDataCharacter( QString& name, QString& corpName, QString& charId,
                             QString& charName );

        /*!
        return the charName
        */
        const QString& name();

        /*!
        return the corp name
        */
        const QString& corpName();

        /*!
        return the charId
        */
        const QString& charId();

        /*!
        return the corpId
        */
        const QString& corpId();

    private:
        QString _name;
        QString _charId;
        QString _corpId;
        QString _corpName;
};

class EveApiDataCharacters: public EveApiData
{
    public:
        /*!
        construct the data container for account balance
        */
        EveApiDataCharacters();

        /*!
        Add character
        */
        void addCharacter( QString& name, QString& corpName, QString& charId,
                           QString& corpId );

        /*!
        get all characters
        */
        const QList<EveApiDataCharacters>& getCharacters();

    private:
        //! Characters
        QList<EveApiDataCharacter> _characters;
};

#endif
