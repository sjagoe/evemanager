#include <QApplication>

#include "main.hh"

#include <QMessageBox>

#include <QString>
#include <QMap>

Window::Window( QWidget* parent )
    : QWidget( parent )
{
    QString dataPath = QString("data");
    this->_api = new EveApi(dataPath);

    this->_eveSkillTree = new QPushButton("/eve/SkillTree");
    this->_eveRefTypes = new QPushButton("/eve/RefTypes");
    this->_mapSov = new QPushButton("/map/Sovereignty");
    this->_charSheet = new QPushButton("/char/CharacterSheet");
    this->_charTraining = new QPushButton("/char/SkillInTraining");
    this->_charJournal = new QPushButton("/char/WalletJournal");
    this->_corpJournal = new QPushButton("/corp/WalletJournal");
    this->_charWallet = new QPushButton("/char/WalletTransactions");
    this->_corpWallet = new QPushButton("/corp/WalletTransactions");
    this->_charBalance = new QPushButton("/char/AccountBalance");
    this->_corpBalance = new QPushButton("/corp/AccountBalance");
    this->_corpMembers = new QPushButton("/corp/MemberTracking");

    connect( this->_eveSkillTree, SIGNAL(clicked()), this, SLOT(eveSkillTree()));
    connect( this->_eveRefTypes, SIGNAL(clicked()), this, SLOT(eveRefTypes()));
    connect( this->_mapSov, SIGNAL(clicked()), this, SLOT(mapSov()));
    connect( this->_charSheet, SIGNAL(clicked()), this, SLOT(charSheet()));
    connect( this->_charTraining, SIGNAL(clicked()), this, SLOT(charTraining()));
    connect( this->_charJournal, SIGNAL(clicked()), this, SLOT(charJournal()));
    connect( this->_corpJournal, SIGNAL(clicked()), this, SLOT(corpJournal()));
    connect( this->_charWallet, SIGNAL(clicked()), this, SLOT(charWallet()));
    connect( this->_corpWallet, SIGNAL(clicked()), this, SLOT(corpWallet()));
    connect( this->_charBalance, SIGNAL(clicked()), this, SLOT(charBalance()));
    connect( this->_corpBalance, SIGNAL(clicked()), this, SLOT(corpBalance()));
    connect( this->_corpMembers, SIGNAL(clicked()), this, SLOT(corpMembers()));

    QVBoxLayout* l = new QVBoxLayout;
    l->addWidget(this->_eveSkillTree);
    l->addWidget(this->_eveRefTypes);
    l->addWidget(this->_mapSov);
    l->addWidget(this->_charSheet);
    l->addWidget(this->_charTraining);
    l->addWidget(this->_charJournal);
    l->addWidget(this->_corpJournal);
    l->addWidget(this->_charWallet);
    l->addWidget(this->_corpWallet);
    l->addWidget(this->_charBalance);
    l->addWidget(this->_corpBalance);
    l->addWidget(this->_corpMembers);

    this->setLayout(l);

    connect( this->_api,
        SIGNAL(requestComplete( QString, QDomDocument, QString )),
        this, SLOT(requestComplete( QString, QDomDocument, QString )) );
    connect( this->_api,
        SIGNAL(requestFailed( QString, QString, QString )),
        this, SLOT(requestFailed( QString, QString, QString )) );
}


void Window::eveSkillTree()
{
    QMap<QString, QString> params;
    params.insert( QString("userID"), QString("695163") );
    params.insert( QString("apiKey"), QString("VhNtTIJbptLoberHr0RcYFhmusa8aMllvXrqp8D0udzXFly9Xc3EBSmWoSy3clJ3") );
    //QMessageBox::information(this, "button", "clicked", QMessageBox::Ok);
    QString result = this->_api->eve().skillTree( params );
    QMessageBox::information(this, "request", result, QMessageBox::Ok);
}

void Window::eveRefTypes()
{
    QMap<QString, QString> params;
    params.insert( QString("userID"), QString("695163") );
    params.insert( QString("apiKey"), QString("VhNtTIJbptLoberHr0RcYFhmusa8aMllvXrqp8D0udzXFly9Xc3EBSmWoSy3clJ3") );
    //QMessageBox::information(this, "button", "clicked", QMessageBox::Ok);
    QString result = this->_api->eve().refTypes( params );
    QMessageBox::information(this, "request", result, QMessageBox::Ok);
}

void Window::mapSov()
{
    QMap<QString, QString> params;
    params.insert( QString("userID"), QString("695163") );
    params.insert( QString("apiKey"), QString("VhNtTIJbptLoberHr0RcYFhmusa8aMllvXrqp8D0udzXFly9Xc3EBSmWoSy3clJ3") );
    //QMessageBox::information(this, "button", "clicked", QMessageBox::Ok);
    QString result = this->_api->map().sovereignty( params );
    QMessageBox::information(this, "request", result, QMessageBox::Ok);
}

void Window::charSheet()
{
    QMap<QString, QString> params;
    params.insert( QString("userID"), QString("695163") );
    params.insert( QString("characterID"), QString("767637297") );
    params.insert( QString("apiKey"), QString("VhNtTIJbptLoberHr0RcYFhmusa8aMllvXrqp8D0udzXFly9Xc3EBSmWoSy3clJ3") );
    //QMessageBox::information(this, "button", "clicked", QMessageBox::Ok);
    QString result = this->_api->character().characterSheet( params );
    QMessageBox::information(this, "request", result, QMessageBox::Ok);
}

void Window::charTraining()
{
    QMap<QString, QString> params;
    params.insert( QString("userID"), QString("695163") );
    params.insert( QString("characterID"), QString("767637297") );
    params.insert( QString("apiKey"), QString("VhNtTIJbptLoberHr0RcYFhmusa8aMllvXrqp8D0udzXFly9Xc3EBSmWoSy3clJ3") );
    //QMessageBox::information(this, "button", "clicked", QMessageBox::Ok);
    QString result = this->_api->character().skillInTraining( params );
    QMessageBox::information(this, "request", result, QMessageBox::Ok);
}

void Window::charJournal()
{
    QMap<QString, QString> params;
    params.insert( QString("userID"), QString("695163") );
    params.insert( QString("characterID"), QString("767637297") );
    params.insert( QString("apiKey"), QString("iQbt9dFt42VVdhdbjtlOzwW41WJLWkgnL4ImZc0GqOLJOiEkv9E3vSrRJjZWzTbG") );
    //QMessageBox::information(this, "button", "clicked", QMessageBox::Ok);
    QString result = this->_api->character().walletJournal( params );
    QMessageBox::information(this, "request", result, QMessageBox::Ok);
}

void Window::corpJournal()
{
    QMap<QString, QString> params;
    params.insert( QString("userID"), QString("695163") );
    params.insert( QString("characterID"), QString("767637297") );
    params.insert( QString("apiKey"), QString("iQbt9dFt42VVdhdbjtlOzwW41WJLWkgnL4ImZc0GqOLJOiEkv9E3vSrRJjZWzTbG") );
    params.insert( QString( "accountKey" ), QString( "1000" ) );
    //QMessageBox::information(this, "button", "clicked", QMessageBox::Ok);
    QString result = this->_api->corp().walletJournal( params );
    QMessageBox::information(this, "request", result, QMessageBox::Ok);
}

void Window::charWallet()
{
    QMap<QString, QString> params;
    params.insert( QString("userID"), QString("695163") );
    params.insert( QString("characterID"), QString("767637297") );
    params.insert( QString("apiKey"), QString("iQbt9dFt42VVdhdbjtlOzwW41WJLWkgnL4ImZc0GqOLJOiEkv9E3vSrRJjZWzTbG") );
    //QMessageBox::information(this, "button", "clicked", QMessageBox::Ok);
    QString result = this->_api->character().walletTransactions( params );
    QMessageBox::information(this, "request", result, QMessageBox::Ok);
}

void Window::corpWallet()
{
    QMap<QString, QString> params;
    params.insert( QString("userID"), QString("695163") );
    params.insert( QString("characterID"), QString("767637297") );
    params.insert( QString("apiKey"), QString("iQbt9dFt42VVdhdbjtlOzwW41WJLWkgnL4ImZc0GqOLJOiEkv9E3vSrRJjZWzTbG") );
    params.insert( QString( "accountKey" ), QString( "1006" ) );
    //QMessageBox::information(this, "button", "clicked", QMessageBox::Ok);
    QString result = this->_api->corp().walletTransactions( params );
    QMessageBox::information(this, "request", result, QMessageBox::Ok);
}

void Window::charBalance()
{
    QMap<QString, QString> params;
    params.insert( QString("userID"), QString("695163") );
    params.insert( QString("characterID"), QString("767637297") );
    params.insert( QString("apiKey"), QString("iQbt9dFt42VVdhdbjtlOzwW41WJLWkgnL4ImZc0GqOLJOiEkv9E3vSrRJjZWzTbG") );
    //QMessageBox::information(this, "button", "clicked", QMessageBox::Ok);
    QString result = this->_api->character().accountBalance( params );
    QMessageBox::information(this, "request", result, QMessageBox::Ok);
}

void Window::corpBalance()
{
    QMap<QString, QString> params;
    params.insert( QString("userID"), QString("695163") );
    params.insert( QString("characterID"), QString("767637297") );
    params.insert( QString("apiKey"), QString("iQbt9dFt42VVdhdbjtlOzwW41WJLWkgnL4ImZc0GqOLJOiEkv9E3vSrRJjZWzTbG") );
    //QMessageBox::information(this, "button", "clicked", QMessageBox::Ok);
    QString result = this->_api->corp().accountBalance( params );
    QMessageBox::information(this, "request", result, QMessageBox::Ok);
}

void Window::corpMembers()
{
    QMap<QString, QString> params;
    params.insert( QString("userID"), QString("695163") );
    params.insert( QString("characterID"), QString("767637297") );
    params.insert( QString("apiKey"), QString("iQbt9dFt42VVdhdbjtlOzwW41WJLWkgnL4ImZc0GqOLJOiEkv9E3vSrRJjZWzTbG") );
    //QMessageBox::information(this, "button", "clicked", QMessageBox::Ok);
    QString result = this->_api->corp().memberTracking( params );
    QMessageBox::information(this, "request", result, QMessageBox::Ok);
}


void Window::requestComplete( QString id, QDomDocument result, QString httpResponse )
{
    QString resultEmpty = " - empty Doc - ";
    if (!result.isNull())
    {
        resultEmpty = " - not empty Doc - ";
    }
    resultEmpty = resultEmpty.prepend( id );
    resultEmpty = resultEmpty.append( httpResponse );
    QMessageBox::information(this, "result", resultEmpty, QMessageBox::Ok);
}

void Window::requestFailed( QString id, QString error, QString httpResponse )
{
    QString err = id;
    err = err.append(" - ");
    err = err.append(error);
    err = err.append(" - ");
    err = err.append(httpResponse);
    QMessageBox::information(this, "result", err, QMessageBox::Ok);
}

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    Window window;
    window.show();

    return app.exec();
}
