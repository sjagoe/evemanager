
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
#include <QMap>
#include <QMetaType>
#include <QSignalSpy>
#include <QString>

using EveApi::CharactersParser;
using EveApi::CharactersData;

typedef QMap<QString, QMap<QString, QString> > threemap;

Q_DECLARE_METATYPE(QSharedPointer<CharactersData>);
Q_DECLARE_METATYPE(threemap);

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

    QMap<QString, QMap<QString, QString> > expected;
    QMap<QString, QString> inner;
    inner.insert(QString("name"), QString("Mary"));
    inner.insert(QString("characterID"), QString("150267069"));
    inner.insert(QString("corporationName"), QString("Starbase Anchoring Corp"));
    inner.insert(QString("corporationID"), QString("150279367"));
    expected.insert(QString("150267069"), inner);
    inner.clear();
    inner.insert(QString("name"), QString("Marcus"));
    inner.insert(QString("characterID"), QString("150302299"));
    inner.insert(QString("corporationName"), QString("Marcus Corp"));
    inner.insert(QString("corporationID"), QString("150333466"));
    expected.insert(QString("150302299"), inner);
    inner.clear();
    inner.insert(QString("name"), QString("Dieinafire"));
    inner.insert(QString("characterID"), QString("150340823"));
    inner.insert(QString("corporationName"), QString("Center for Advanced Studies"));
    inner.insert(QString("corporationID"), QString("1000169"));
    expected.insert(QString("150340823"), inner);

    QTest::addColumn<QString>("id");
    QTest::addColumn<QString>("xml");
    QTest::addColumn<QString>("httpResponse");
    QTest::addColumn<QDateTime>("cacheExpireTime");
    QTest::addColumn<QMap<QString, QMap<QString, QString> > >("expected");

    QTest::newRow("three characters") << id << xmlData << http << fakeTime << expected;
}

void CharactersParserTest::parse()
{
    qRegisterMetaType<QSharedPointer<CharactersData> >("QSharedPointer<CharactersData>");

    QFETCH(QString, id);
    QFETCH(QString, xml);
    QFETCH(QString, httpResponse);
    QFETCH(QDateTime, cacheExpireTime);
    QFETCH(threemap, expected); // QMap<QString, QMap<QString, QString> >

    CharactersParser* parser = new CharactersParser();
    QSignalSpy spy(parser, SIGNAL(requestComplete( QString, QSharedPointer<CharactersData>,
                                                   QString, QDateTime)));

    parser->parse(id, xml, httpResponse, cacheExpireTime);

    QList<QVariant> arguments = spy.takeFirst();

    QVERIFY(arguments.at(0).type() == QVariant::String);
    QVERIFY(arguments.at(2).type() == QVariant::String);
    QVERIFY(arguments.at(3).type() == QVariant::DateTime);

    QVERIFY(arguments.at(1).canConvert<QSharedPointer<CharactersData> >() == true);
    QSharedPointer<CharactersData> data = arguments.at(1).value<QSharedPointer<CharactersData> >();

    // TODO: Fine grained checking so that the output of the test is meaningful.
    QCOMPARE(data->getCharacters(), expected);

    delete parser;
}
