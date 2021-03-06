
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

#include <QApplication>

#include "main.hh"

#include <QPushButton>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>

#include <QMessageBox>

#include <QString>
#include <QMap>

#include <QDomDocument>
#include <QDomNode>
#include <QDomElement>

#include "eveapiaccount.hh"
#include "eveapicharacter.hh"
#include "eveapicorporation.hh"
#include "eveapieve.hh"
#include "eveapimap.hh"

Window::Window( QWidget* parent )
    : QWidget( parent )
{
    QString hostName = QString("api.eve-online.com");
//    QString hostName = QString("eveapiproxy.appspot.com");
    QString dataPath = QString("data");
//    int proxyType = 1;
//    QString proxyHost = "proxy.localoffice";
//    quint16 proxyPort = 3128;
    this->_api = new EveApi::EveApi(hostName, dataPath);//, proxyType, proxyHost, proxyPort);
    connect( this->_api,
        SIGNAL(requestComplete( QString, shared_ptr<QDomDocument>, QString, QDateTime, QString )),
        this, SLOT(requestComplete( QString, shared_ptr<QDomDocument>, QString, QDateTime, QString )) );
    connect( this->_api,
        SIGNAL(requestFailed( QString, QString, QString )),
        this, SLOT(requestFailed( QString, QString, QString )) );

    this->_accountCharacters = new QPushButton( "Characters.xml.aspx" );
    this->_eveSkillTree = new QPushButton("SkillTree.xml.aspx");
    this->_eveRefTypes = new QPushButton("RefTypes.xml.aspx");
    this->_eveAllianceList = new QPushButton("AllianceList.xml.aspx");
    this->_eveFacWarStats = new QPushButton("FacWarStats.xml.aspx");
    this->_eveFacWarTopStats = new QPushButton("FacWarTopStats.xml.aspx");
    this->_mapSov = new QPushButton("Sovereignty.xml.aspx");
    this->_mapFacWarSystems = new QPushButton("FacWarSystems.xml.aspx");
    this->_charSheet = new QPushButton("CharacterSheet.xml.aspx");
    this->_charTraining = new QPushButton("SkillInTraining.xml.aspx");
    this->_charJournal = new QPushButton("WalletJournal.xml.aspx");
    this->_corpJournal = new QPushButton("WalletJournal.xml.aspx");
    this->_charWallet = new QPushButton("WalletTransactions.xml.aspx");
    this->_corpWallet = new QPushButton("WalletTransactions.xml.aspx");
    this->_charBalance = new QPushButton("AccountBalance.xml.aspx");
    this->_corpBalance = new QPushButton("AccountBalance.xml.aspx");
    this->_corpMembers = new QPushButton("MemberTracking.xml.aspx");
    this->_charFacWarStats = new QPushButton("FacWarStats.xml.aspx");
    this->_corpFacWarStats = new QPushButton("FacWarStats.xml.aspx");

    connect( this->_accountCharacters, SIGNAL(clicked()), this, SLOT(accountCharacters()));
    connect( this->_eveSkillTree, SIGNAL(clicked()), this, SLOT(eveSkillTree()));
    connect( this->_eveRefTypes, SIGNAL(clicked()), this, SLOT(eveRefTypes()));
    connect( this->_eveAllianceList, SIGNAL(clicked()), this, SLOT(eveAllianceList()));
    connect( this->_eveFacWarStats, SIGNAL(clicked()), this, SLOT(eveFacWarStats()));
    connect( this->_eveFacWarTopStats, SIGNAL(clicked()), this, SLOT(eveFacWarTopStats()));
    connect( this->_mapSov, SIGNAL(clicked()), this, SLOT(mapSov()));
    connect( this->_mapFacWarSystems, SIGNAL(clicked()), this, SLOT(eveFacWarTopStats()));
    connect( this->_charSheet, SIGNAL(clicked()), this, SLOT(charSheet()));
    connect( this->_charTraining, SIGNAL(clicked()), this, SLOT(charTraining()));
    connect( this->_charJournal, SIGNAL(clicked()), this, SLOT(charJournal()));
    connect( this->_corpJournal, SIGNAL(clicked()), this, SLOT(corpJournal()));
    connect( this->_charWallet, SIGNAL(clicked()), this, SLOT(charWallet()));
    connect( this->_corpWallet, SIGNAL(clicked()), this, SLOT(corpWallet()));
    connect( this->_charBalance, SIGNAL(clicked()), this, SLOT(charBalance()));
    connect( this->_corpBalance, SIGNAL(clicked()), this, SLOT(corpBalance()));
    connect( this->_corpMembers, SIGNAL(clicked()), this, SLOT(corpMembers()));
    connect( this->_charFacWarStats, SIGNAL(clicked()), this, SLOT(charFacWarStats()));
    connect( this->_corpFacWarStats, SIGNAL(clicked()), this, SLOT(corpFacWarStats()));

    this->_account = new QGroupBox( "/account/" );
    QVBoxLayout* inaccountlayout = new QVBoxLayout;
    inaccountlayout->addWidget( this->_accountCharacters );
    this->_account->setLayout( inaccountlayout );

    this->_eve = new QGroupBox("/eve/");
    QVBoxLayout* inevelayout = new QVBoxLayout;
    inevelayout->addWidget(this->_eveSkillTree);
    inevelayout->addWidget(this->_eveRefTypes);
    inevelayout->addWidget(this->_eveAllianceList);
    inevelayout->addWidget(this->_eveFacWarStats);
    inevelayout->addWidget(this->_eveFacWarTopStats);
    this->_eve->setLayout( inevelayout );

    this->_map = new QGroupBox("/map/");
    QVBoxLayout* inmaplayout = new QVBoxLayout;
    inmaplayout->addWidget(this->_mapSov);
    inmaplayout->addWidget(this->_mapFacWarSystems);
    this->_map->setLayout( inmaplayout );

//    QVBoxLayout* left = new QVBoxLayout;
//    left->addWidget(this->_eve);
//    left->addWidget(this->_map);
//    left->addStretch();

    this->_char = new QGroupBox("/char/");
    QVBoxLayout* incharlayout = new QVBoxLayout;
    incharlayout->addWidget(this->_charSheet);
    incharlayout->addWidget(this->_charTraining);
    incharlayout->addWidget(this->_charJournal);
    incharlayout->addWidget(this->_charWallet);
    incharlayout->addWidget(this->_charBalance);
    incharlayout->addWidget(this->_charFacWarStats);
    this->_char->setLayout( incharlayout );

    this->_corp = new QGroupBox("/corp/");
    QVBoxLayout* incorplayout = new QVBoxLayout;
    incorplayout->addWidget(this->_corpJournal);
    incorplayout->addWidget(this->_corpWallet);
    incorplayout->addWidget(this->_corpBalance);
    incorplayout->addWidget(this->_corpMembers);
    incorplayout->addWidget(this->_corpFacWarStats);
    this->_corp->setLayout( incorplayout );

    QGridLayout* buttons = new QGridLayout;
    buttons->addWidget( this->_account, 0, 0 );
    buttons->addWidget( this->_eve, 1, 0, 2, 1 );
    buttons->addWidget( this->_char, 0, 1, 3, 1);
    buttons->addWidget( this->_corp, 0, 2, 2, 1);
    buttons->addWidget( this->_map, 2, 2 );

    this->_apiInfo = new QGroupBox("API parameters");

    this->_lblUserID = new QLabel("User ID");
    this->_lblLimitedApiKey = new QLabel( "Limited API Key" );
    this->_lblFullApiKey = new QLabel( "Full API Key (needed for char money stuff, and all corp stuff)" );
    this->_lblCharacterID = new QLabel( "Character ID" );
    this->_lblAccountID = new QLabel( "Account Key" );
    this->_lblBeforeRefID = new QLabel( "Before Ref ID (Journal Walking)" );
    this->_lblBeforeTransID = new QLabel( "Before Trans ID (Transaction Walking)" );

    this->_edtUserID = new QLineEdit;
    this->_edtLimitedApiKey = new QLineEdit;
    this->_edtFullApiKey = new QLineEdit;
    this->_edtCharacterID = new QLineEdit;
    this->_edtAccountID = new QLineEdit;
    this->_edtBeforeRefID = new QLineEdit;
    this->_edtBeforeTransID = new QLineEdit;

    QGridLayout* inapigrid = new QGridLayout;
    inapigrid->addWidget(this->_lblAccountID, 0, 0);
    inapigrid->addWidget(this->_edtAccountID, 1, 0);
    inapigrid->addWidget(this->_lblBeforeRefID, 0, 1);
    inapigrid->addWidget(this->_edtBeforeRefID, 1, 1);
    inapigrid->addWidget(this->_lblBeforeTransID, 0, 2);
    inapigrid->addWidget(this->_edtBeforeTransID, 1, 2);

    QGridLayout* apigrid = new QGridLayout;
    apigrid->addWidget(this->_lblUserID, 0, 0);
    apigrid->addWidget(this->_edtUserID, 1, 0);
    apigrid->addWidget(this->_lblCharacterID, 0, 1);
    apigrid->addWidget(this->_edtCharacterID, 1, 1);
    apigrid->addWidget(this->_lblLimitedApiKey, 2, 0, 1, 2 );
    apigrid->addWidget(this->_edtLimitedApiKey, 3, 0, 1, 2 );
    apigrid->addWidget(this->_lblFullApiKey, 4, 0, 1, 2 );
    apigrid->addWidget(this->_edtFullApiKey, 5, 0, 1, 2 );
    apigrid->addLayout(inapigrid, 6, 0, 1, 2 );

    this->_apiInfo->setLayout(apigrid);

    this->_edtResult = new QTextEdit;
    this->_edtResult->setReadOnly(true);
    this->_edtId = new QLineEdit;
    this->_edtId->setReadOnly(true);
    this->_edtResponse = new QLineEdit;
    this->_edtResponse->setReadOnly(true);

    this->_lblResult = new QLabel( "Result from API" );
    this->_lblId = new QLabel( "Internal Request ID" );
    this->_lblResponse = new QLabel( "Response from HTTP Server" );


    this->_lblCacheTime = new QLabel("Cache Expires (UTC, i.e. EVE Time)");
    this->_edtCacheTime = new QLineEdit;

    this->_edtCacheTime->setReadOnly(true);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(this->_apiInfo);
    layout->addLayout(buttons);
    layout->addWidget(this->_lblId);
    layout->addWidget(this->_edtId);
    layout->addWidget(this->_lblResponse);
    layout->addWidget(this->_edtResponse);
    layout->addWidget(this->_lblResult);
    layout->addWidget(this->_edtResult);
    layout->addWidget(this->_lblCacheTime);
    layout->addWidget(this->_edtCacheTime);

    this->setLayout(layout);
}

void Window::accountCharacters()
{
    QMap<QString, QString> params;
    params.insert( QString("userID"), this->_edtUserID->text() );
    params.insert( QString("apiKey"), this->_edtLimitedApiKey->text() );
    //QMessageBox::information(this, "button", "clicked", QMessageBox::Ok);
    QString result = this->_api->account().characters( params );
    QMessageBox::information(this, "request", result, QMessageBox::Ok);
}

void Window::eveSkillTree()
{
    QMap<QString, QString> params;
    params.insert( QString("userID"), this->_edtUserID->text() );
    params.insert( QString("apiKey"), this->_edtLimitedApiKey->text() );
    //QMessageBox::information(this, "button", "clicked", QMessageBox::Ok);
    QString result = this->_api->eve().skillTree( params );
    QMessageBox::information(this, "request", result, QMessageBox::Ok);
}

void Window::eveRefTypes()
{
    QMap<QString, QString> params;
    params.insert( QString("userID"), this->_edtUserID->text() );
    params.insert( QString("apiKey"), this->_edtLimitedApiKey->text() );
    //QMessageBox::information(this, "button", "clicked", QMessageBox::Ok);
    QString result = this->_api->eve().refTypes( params );
    QMessageBox::information(this, "request", result, QMessageBox::Ok);
}

void Window::eveAllianceList()
{
    QMap<QString, QString> params;
    params.insert( QString("userID"), this->_edtUserID->text() );
    params.insert( QString("apiKey"), this->_edtLimitedApiKey->text() );
    //QMessageBox::information(this, "button", "clicked", QMessageBox::Ok);
    QString result = this->_api->eve().allianceList( params );
    QMessageBox::information(this, "request", result, QMessageBox::Ok);
}

void Window::mapSov()
{
    QMap<QString, QString> params;
    params.insert( QString("userID"), this->_edtUserID->text() );
    params.insert( QString("apiKey"), this->_edtLimitedApiKey->text() );
    //QMessageBox::information(this, "button", "clicked", QMessageBox::Ok);
    QString result = this->_api->map().sovereignty( params );
    QMessageBox::information(this, "request", result, QMessageBox::Ok);
}

void Window::charSheet()
{
    QMap<QString, QString> params;
    params.insert( QString("userID"), this->_edtUserID->text() );
    params.insert( QString("characterID"), this->_edtCharacterID->text() );
    params.insert( QString("apiKey"), this->_edtLimitedApiKey->text() );
    //QMessageBox::information(this, "button", "clicked", QMessageBox::Ok);
    QString result = this->_api->character().characterSheet( params );
    QMessageBox::information(this, "request", result, QMessageBox::Ok);
}

void Window::charTraining()
{
    QMap<QString, QString> params;
    params.insert( QString("userID"), this->_edtUserID->text() );
    params.insert( QString("characterID"), this->_edtCharacterID->text() );
    params.insert( QString("apiKey"), this->_edtLimitedApiKey->text() );
    //QMessageBox::information(this, "button", "clicked", QMessageBox::Ok);
    QString result = this->_api->character().skillInTraining( params );
    QMessageBox::information(this, "request", result, QMessageBox::Ok);
}

void Window::charJournal()
{
    QMap<QString, QString> params;
    params.insert( QString("userID"), this->_edtUserID->text() );
    params.insert( QString("characterID"), this->_edtCharacterID->text() );
    params.insert( QString("apiKey"), this->_edtFullApiKey->text() );
    //QMessageBox::information(this, "button", "clicked", QMessageBox::Ok);
    if (!this->_edtBeforeRefID->text().isEmpty())
    {
        params.insert( QString("beforeRefID"), this->_edtBeforeRefID->text() );
    }
    QString result = this->_api->character().walletJournal( params );
    QMessageBox::information(this, "request", result, QMessageBox::Ok);
}

void Window::corpJournal()
{
    QMap<QString, QString> params;
    params.insert( QString("userID"), this->_edtUserID->text() );
    params.insert( QString("characterID"), this->_edtCharacterID->text() );
    params.insert( QString("apiKey"), this->_edtFullApiKey->text() );
    if (!this->_edtAccountID->text().isEmpty())
    {
        params.insert( QString( "accountKey" ), this->_edtAccountID->text() );
    }
    if (!this->_edtBeforeRefID->text().isEmpty())
    {
        params.insert( QString("beforeRefID"), this->_edtBeforeRefID->text() );
    }
    //QMessageBox::information(this, "button", "clicked", QMessageBox::Ok);
    QString result = this->_api->corp().walletJournal( params );
    QMessageBox::information(this, "request", result, QMessageBox::Ok);
}

void Window::charWallet()
{
    QMap<QString, QString> params;
    params.insert( QString("userID"), this->_edtUserID->text() );
    params.insert( QString("characterID"), this->_edtCharacterID->text() );
    params.insert( QString("apiKey"), this->_edtFullApiKey->text() );
    if (!this->_edtBeforeTransID->text().isEmpty())
    {
        params.insert( QString("beforeTransID"), this->_edtBeforeTransID->text() );
    }
    //QMessageBox::information(this, "button", "clicked", QMessageBox::Ok);
    QString result = this->_api->character().walletTransactions( params );
    QMessageBox::information(this, "request", result, QMessageBox::Ok);
}

void Window::corpWallet()
{
    QMap<QString, QString> params;
    params.insert( QString("userID"), this->_edtUserID->text() );
    params.insert( QString("characterID"), this->_edtCharacterID->text() );
    params.insert( QString("apiKey"), this->_edtFullApiKey->text() );
    if (!this->_edtAccountID->text().isEmpty())
    {
        params.insert( QString( "accountKey" ), this->_edtAccountID->text() );
    }
    if (!this->_edtBeforeTransID->text().isEmpty())
    {
        params.insert( QString("beforeTransID"), this->_edtBeforeTransID->text() );
    }
    //QMessageBox::information(this, "button", "clicked", QMessageBox::Ok);
    QString result = this->_api->corp().walletTransactions( params );
    QMessageBox::information(this, "request", result, QMessageBox::Ok);
}

void Window::charBalance()
{
    QMap<QString, QString> params;
    params.insert( QString("userID"), this->_edtUserID->text() );
    params.insert( QString("characterID"), this->_edtCharacterID->text() );
    params.insert( QString("apiKey"), this->_edtFullApiKey->text() );
    //QMessageBox::information(this, "button", "clicked", QMessageBox::Ok);
    QString result = this->_api->character().accountBalance( params );
    QMessageBox::information(this, "request", result, QMessageBox::Ok);
}

void Window::corpBalance()
{
    QMap<QString, QString> params;
    params.insert( QString("userID"), this->_edtUserID->text() );
    params.insert( QString("characterID"), this->_edtCharacterID->text() );
    params.insert( QString("apiKey"), this->_edtFullApiKey->text() );
    //QMessageBox::information(this, "button", "clicked", QMessageBox::Ok);
    QString result = this->_api->corp().accountBalance( params );
    QMessageBox::information(this, "request", result, QMessageBox::Ok);
}

void Window::corpMembers()
{
    QMap<QString, QString> params;
    params.insert( QString("userID"), this->_edtUserID->text() );
    params.insert( QString("characterID"), this->_edtCharacterID->text() );
    params.insert( QString("apiKey"), this->_edtFullApiKey->text() );
    //QMessageBox::information(this, "button", "clicked", QMessageBox::Ok);
    QString result = this->_api->corp().memberTracking( params );
    QMessageBox::information(this, "Request sent", result, QMessageBox::Ok);
}

void Window::charFacWarStats()
{
    QMap<QString, QString> params;
    params.insert( QString("userID"), this->_edtUserID->text() );
    params.insert( QString("characterID"), this->_edtCharacterID->text() );
    params.insert( QString("apiKey"), this->_edtFullApiKey->text() );
    //QMessageBox::information(this, "button", "clicked", QMessageBox::Ok);
    QString result = this->_api->character().facWarStats( params );
    QMessageBox::information(this, "Request sent", result, QMessageBox::Ok);
}

void Window::corpFacWarStats()
{
    QMap<QString, QString> params;
    params.insert( QString("userID"), this->_edtUserID->text() );
    params.insert( QString("characterID"), this->_edtCharacterID->text() );
    params.insert( QString("apiKey"), this->_edtFullApiKey->text() );
    //QMessageBox::information(this, "button", "clicked", QMessageBox::Ok);
    QString result = this->_api->corp().facWarStats( params );
    QMessageBox::information(this, "Request sent", result, QMessageBox::Ok);
}

void Window::eveFacWarStats()
{
    QMap<QString, QString> params;
    params.insert( QString("userID"), this->_edtUserID->text() );
    params.insert( QString("apiKey"), this->_edtLimitedApiKey->text() );
    //QMessageBox::information(this, "button", "clicked", QMessageBox::Ok);
    QString result = this->_api->eve().facWarStats( params );
    QMessageBox::information(this, "Request sent", result, QMessageBox::Ok);
}

void Window::eveFacWarTopStats()
{
    QMap<QString, QString> params;
    params.insert( QString("userID"), this->_edtUserID->text() );
    params.insert( QString("apiKey"), this->_edtLimitedApiKey->text() );
    //QMessageBox::information(this, "button", "clicked", QMessageBox::Ok);
    QString result = this->_api->eve().facWarTopStats( params );
    QMessageBox::information(this, "Request sent", result, QMessageBox::Ok);
}

void Window::mapFacWarSystems()
{
    QMap<QString, QString> params;
    params.insert( QString("userID"), this->_edtUserID->text() );
    params.insert( QString("apiKey"), this->_edtLimitedApiKey->text() );
    //QMessageBox::information(this, "button", "clicked", QMessageBox::Ok);
    QString result = this->_api->map().facWarSystems( params );
    QMessageBox::information(this, "Request sent", result, QMessageBox::Ok);
}


void Window::requestComplete( QString id, shared_ptr<QDomDocument> result, QString httpResponse, QDateTime cacheTime, QString )
{
    this->_edtId->setText(id);
    this->_edtResult->setText( result->toString(4) );
    this->_edtResponse->setText( httpResponse );
    this->_edtCacheTime->setText( cacheTime.toString() );
}

void Window::requestFailed( QString id, QString error, QString httpResponse )
{
    this->_edtId->setText(id);
    this->_edtResult->setText( error );
    this->_edtResponse->setText( httpResponse );
    this->_edtCacheTime->clear();
}

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    Window window;
    window.show();

    return app.exec();
}
