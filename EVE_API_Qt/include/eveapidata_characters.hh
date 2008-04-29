
/*
 * Copyright 2007-2008 Simon Jagoe
 *
 * This file is part of EVE_API_Qt.
 *
 * EVE_API_Qt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EVE_API_Qt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EVE_API_Qt.  If not, see <http://www.gnu.org/licenses/>.
 */

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
        QString _corpName;
        QString _charId;
        QString _corpId;
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
        const QList<EveApiDataCharacter>& getCharacters();

    private:
        //! Characters
        QList<EveApiDataCharacter> _characters;
};

#endif
