
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

#include "charactersparser_test.h"

#include "charactersparser.h"
#include "charactersdata.h"

#include <boost/shared_ptr.hpp>

#include <QDateTime>
#include <QList>
#include <QMap>
#include <QMetaType>
#include <QSignalSpy>
#include <QString>

using EveApi::CharactersParser;
using EveApi::CharactersData;
using EveApi::CharacterData;

//typedef QMap<QString, QMap<QString, QString> > threemap;
typedef QList<CharacterData> characterList;

Q_DECLARE_METATYPE(shared_ptr<CharactersData>);
Q_DECLARE_METATYPE(CharactersData);
Q_DECLARE_METATYPE(CharacterData);
Q_DECLARE_METATYPE(characterList);

void CharactersParserTest::parse_data()
{
    QString xmlData = "";
    xmlData.append("<?xml version='1.0' encoding='UTF-8'?>");
    xmlData.append("<eveapi version=\"1\">");
    xmlData.append("  <currentTime>2007-12-12 11:48:50</currentTime>");
    xmlData.append("  <result>");
    xmlData.append("    <rowset name=\"characters\" key=\"characterID\" columns=\"name,characterID,corporationName,corporationID\">");
    xmlData.append("      <row name=\"Mary\" characterID=\"150267069\"");
    xmlData.append("           corporationName=\"Starbase Anchoring Corp\" corporationID=\"150279367\" />");
    xmlData.append("      <row name=\"Marcus\" characterID=\"150302299\"");
    xmlData.append("           corporationName=\"Marcus Corp\" corporationID=\"150333466\" />");
    xmlData.append("      <row name=\"Dieinafire\" characterID=\"150340823\"");
    xmlData.append("           corporationName=\"Center for Advanced Studies\" corporationID=\"1000169\" />");
    xmlData.append("    </rowset>");
    xmlData.append("  </result>");
    xmlData.append("  <cachedUntil>2007-12-12 12:48:50</cachedUntil>");
    xmlData.append("</eveapi>");

    QString id = "Fake ID";
    QString http = "200";
    QDateTime fakeTime;

    QList<CharacterData> characters;
    characters << CharacterData("Mary", "150267069", "Starbase Anchoring Corp", "150279367");
    characters << CharacterData("Marcus", "150302299", "Marcus Corp", "150333466");
    characters << CharacterData("Dieinafire", "150340823", "Center for Advanced Studies", "1000169");
    CharactersData expected(1, fakeTime, fakeTime, characters);

    QTest::addColumn<QString>("id");
    QTest::addColumn<QString>("xml");
    QTest::addColumn<QString>("httpResponse");
    QTest::addColumn<QDateTime>("cacheExpireTime");
    QTest::addColumn<CharactersData>("expected");

    QTest::newRow("three characters") << id << xmlData << http << fakeTime << expected;
}

void CharactersParserTest::parse()
{
    qRegisterMetaType<shared_ptr<CharactersData> >("shared_ptr<CharactersData>");

    QFETCH(QString, id);
    QFETCH(QString, xml);
    QFETCH(QString, httpResponse);
    QFETCH(QDateTime, cacheExpireTime);
    QFETCH(CharactersData, expected);

    CharactersParser* parser = new CharactersParser();
    QSignalSpy spy(parser, SIGNAL(requestComplete( QString, shared_ptr<CharactersData>,
                                                   QString, QDateTime)));

    parser->parse(id, xml, httpResponse, cacheExpireTime);

    QList<QVariant> arguments = spy.takeFirst();

    QVERIFY(arguments.at(0).type() == QVariant::String);
    QVERIFY(arguments.at(2).type() == QVariant::String);
    QVERIFY(arguments.at(3).type() == QVariant::DateTime);

    QVERIFY(arguments.at(1).canConvert<shared_ptr<CharactersData> >() == true);
    shared_ptr<CharactersData> data = arguments.at(1).value<shared_ptr<CharactersData> >();

    QCOMPARE(*data, expected);

    delete parser;
}

void CharactersParserTest::charactersDataEquality_data()
{
    QTest::addColumn<int>("version");
    QTest::addColumn<QDateTime>("date");
    QTest::addColumn<characterList>("characters");
    QTest::addColumn<CharactersData>("one");
    QTest::addColumn<CharactersData>("two");

    int version = 1;
    QDateTime fakeTime;
    QList<CharacterData> characters;
    characters << CharacterData("Mary", "150267069", "Starbase Anchoring Corp", "150279367");
    characters << CharacterData("Marcus", "150302299", "Marcus Corp", "150333466");
    characters << CharacterData("Dieinafire", "150340823", "Center for Advanced Studies", "1000169");

    int versionOnly = 1;
    QDateTime fakeTimeOnly;
    QList<CharacterData> charactersOnly;
    charactersOnly << CharacterData("Mary", "150267069", "Starbase Anchoring Corp", "150279367");
    charactersOnly << CharacterData("Marcus", "150302299", "Marcus Corp", "150333466");
    charactersOnly << CharacterData("Dieinafire", "150340823", "Center for Advanced Studies", "1000169");
    CharactersData only(versionOnly, fakeTimeOnly, fakeTimeOnly, charactersOnly);

    QTest::newRow("rowOne") << version << fakeTime << characters << only << only;

    int version1 = 10;
    QDateTime fakeTime1;
    fakeTime1.setTime_t(100);
    QList<CharacterData> characters1;
    characters1 << CharacterData("Mary", "150267069", "Starbase Anchoring Corp", "150279367");
    characters1 << CharacterData("Marcus", "150302299", "Marcus Corp", "150333466");
    characters1 << CharacterData("Dieinafire", "150340823", "Center for Advanced Studies", "1000169");
    CharactersData one(version1, fakeTime1, fakeTime1, characters1);

    // The version and times are purposefully not checked. The _meaningful_ contents of the server response were the same...

    int version2 = 100;
    QDateTime fakeTime2;
    fakeTime2.setTime_t(90000);
    QList<CharacterData> characters2;
    characters2 << CharacterData("Mary", "150267069", "Starbase Anchoring Corp", "150279367");
    characters2 << CharacterData("Marcus", "150302299", "Marcus Corp", "150333466");
    characters2 << CharacterData("Dieinafire", "150340823", "Center for Advanced Studies", "1000169");
    CharactersData two(version2, fakeTime2, fakeTime2, characters2);

    QTest::newRow("rowTwo") << version << fakeTime << characters << one << two;
}

void CharactersParserTest::charactersDataEquality()
{
    QFETCH(characterList, characters);
    QFETCH(CharactersData, one);
    QFETCH(CharactersData, two);

    QCOMPARE(one, two);
    QCOMPARE(one.characters(), characters);
    QCOMPARE(two.characters(), characters);
    QCOMPARE(one.characters(), two.characters());

    for (int i = 0; i < characters.length(); ++i)
    {
        QCOMPARE(one.characters().at(i), characters.at(i));
        QCOMPARE(two.characters().at(i), characters.at(i));
        QCOMPARE(one.characters().at(i), two.characters().at(i));

        QCOMPARE(one.characters().at(i).name(), characters.at(i).name());
        QCOMPARE(two.characters().at(i).name(), characters.at(i).name());
        QCOMPARE(one.characters().at(i).name(), two.characters().at(i).name());
        QCOMPARE(one.characters().at(i).characterID(), characters.at(i).characterID());
        QCOMPARE(two.characters().at(i).characterID(), characters.at(i).characterID());
        QCOMPARE(one.characters().at(i).characterID(), two.characters().at(i).characterID());
        QCOMPARE(one.characters().at(i).corporationName(), characters.at(i).corporationName());
        QCOMPARE(two.characters().at(i).corporationName(), characters.at(i).corporationName());
        QCOMPARE(one.characters().at(i).corporationName(), two.characters().at(i).corporationName());
        QCOMPARE(one.characters().at(i).corporationID(), characters.at(i).corporationID());
        QCOMPARE(two.characters().at(i).corporationID(), characters.at(i).corporationID());
        QCOMPARE(one.characters().at(i).corporationID(), two.characters().at(i).corporationID());
    }
}

void CharactersParserTest::charactersDataInequality_data()
{
    QTest::addColumn<CharactersData>("one");
    QTest::addColumn<CharactersData>("two");

    int version = 1;
    QDateTime fakeTime;
    fakeTime.setTime_t(10);

    QList<CharacterData> characters1;
    characters1 << CharacterData("1name1", "1id1", "1cname1", "1cid1");
    characters1 << CharacterData("1name2", "1id2", "1cname2", "1cid2");
    characters1 << CharacterData("1name3", "1id3", "1cname3", "1cid3");
    CharactersData one(version, fakeTime, fakeTime, characters1);

    QList<CharacterData> characters2;
    characters2 << CharacterData("2name1", "2id1", "2cname1", "2cid1");
    characters2 << CharacterData("2name2", "2id2", "2cname2", "2cid2");
    characters2 << CharacterData("2name3", "2id3", "2cname3", "2cid3");
    CharactersData two(version, fakeTime, fakeTime, characters2);

    QTest::newRow("DifferentCharacters") << one << two;


    QList<CharacterData> characters3;
    characters1 << CharacterData("1name1", "1id1", "1cname1", "1cid1");
    characters1 << CharacterData("1name2", "1id2", "1cname2", "1cid2");
    characters1 << CharacterData("1name3", "1id3", "1cname3", "1cid3");
    CharactersData three(version, fakeTime, fakeTime, characters1);

    QList<CharacterData> characters4;
    characters2 << CharacterData("1name1", "1id1", "1cname1", "1cid1");
    CharactersData four(version, fakeTime, fakeTime, characters2);

    QTest::newRow("MissingCharacters") << three << four;
}

void CharactersParserTest::charactersDataInequality()
{
    QFETCH(CharactersData, one);
    QFETCH(CharactersData, two);

    QVERIFY(one != two);
    QVERIFY(one.characters() != two.characters());

    if (one.characters().length() == two.characters().length())
    {
        for (int i = 0; i < one.characters().length(); ++i)
        {
            QVERIFY(one.characters().at(i) != two.characters().at(i));
            QVERIFY(one.characters().at(i).name() != two.characters().at(i).name());
            QVERIFY(one.characters().at(i).characterID() != two.characters().at(i).characterID());
            QVERIFY(one.characters().at(i).corporationName() != two.characters().at(i).corporationName());
            QVERIFY(one.characters().at(i).corporationID() != two.characters().at(i).corporationID());
        }
    }
}
