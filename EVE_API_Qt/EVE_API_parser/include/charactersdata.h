
/*
 * Copyright 2009 Simon Jagoe
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

/*
<?xml version='1.0' encoding='UTF-8'?>
<eveapi version="1">
  <currentTime>2007-12-12 11:48:50</currentTime>
  <result>
    <rowset name="characters" key="characterID" columns="name,characterID,corporationName,corporationID">
      <row name="Mary" characterID="150267069"
           corporationName="Starbase Anchoring Corp" corporationID="150279367" />
      <row name="Marcus" characterID="150302299"
           corporationName="Marcus Corp" corporationID="150333466" />
      <row name="Dieinafire" characterID="150340823"
           corporationName="Center for Advanced Studies" corporationID="1000169" />
    </rowset>
  </result>
  <cachedUntil>2007-12-12 12:48:50</cachedUntil>
</eveapi>
 */

#ifndef CHARACTERSDATA_H
#define CHARACTERSDATA_H

#include "abstracteveapidata.hh"

#include <QMap>
#include <QString>
#include <QStringList>

namespace EveApi
{
    class CharactersData: public AbstractData
    {
    public:
        CharactersData( const int& version,
                        const QDateTime& currentTime,
                        const QDateTime& cachedUntil,
                        Rowset<void*>* rowset );

        ~CharactersData();

        QMap<QString, QString> getCharacterNames();

        QMap<QString, QMap<QString, QString> > getCharacters();

    private:
        Rowset<void*>* _characters;
    };
};

#endif // CHARACTERSDATA_H
