#ifndef __MAIN_HH__
#define __MAIN_HH__

#include <QWidget>

#include <boost/shared_ptr.hpp>

#include "eveapi.hh"

using boost::shared_ptr;

class QDomDocument;

class QPushButton;
class QGroupBox;
class QTextEdit;
class QLineEdit;
class QLabel;

class Window: public QWidget
{
    Q_OBJECT
    public:
        Window( QWidget* parent = 0 );

    private:
        QPushButton* _accountCharacters;
        QPushButton* _eveSkillTree;
        QPushButton* _eveRefTypes;
        QPushButton* _eveAllianceList;
        QPushButton* _mapSov;
        QPushButton* _charSheet;
        QPushButton* _charTraining;
        QPushButton* _charJournal;
        QPushButton* _corpJournal;
        QPushButton* _charWallet;
        QPushButton* _corpWallet;
        QPushButton* _charBalance;
        QPushButton* _corpBalance;
        QPushButton* _corpMembers;

        QGroupBox* _account;
        QGroupBox* _eve;
        QGroupBox* _map;
        QGroupBox* _char;
        QGroupBox* _corp;
        QGroupBox* _apiInfo;

        QLabel* _lblUserID;
        QLabel* _lblLimitedApiKey;
        QLabel* _lblFullApiKey;
        QLabel* _lblCharacterID;
        QLabel* _lblAccountID;
        QLabel* _lblBeforeRefID;
        QLabel* _lblBeforeTransID;

        QLineEdit* _edtUserID;
        QLineEdit* _edtLimitedApiKey;
        QLineEdit* _edtFullApiKey;
        QLineEdit* _edtCharacterID;
        QLineEdit* _edtAccountID;
        QLineEdit* _edtBeforeRefID;
        QLineEdit* _edtBeforeTransID;

        QTextEdit* _edtResult;
        QLineEdit* _edtId;
        QLineEdit* _edtResponse;

        QLabel* _lblResult;
        QLabel* _lblId;
        QLabel* _lblResponse;

        QLabel* _lblCacheTime;
        QLineEdit* _edtCacheTime;

        EveApi* _api;

    private slots:
        void accountCharacters();
        void eveSkillTree();
        void eveRefTypes();
        void eveAllianceList();
        void mapSov();
        void charSheet();
        void charTraining();
        void charJournal();
        void corpJournal();
        void charWallet();
        void corpWallet();
        void charBalance();
        void corpBalance();
        void corpMembers();
        void requestComplete( QString id, shared_ptr<QDomDocument> result, QString httpResponse, QDateTime cacheTime );
        void requestFailed( QString id, QString error, QString httpResponse );
};

#endif
