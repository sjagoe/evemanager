
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
        QPushButton* _eveFacWarStats;
        QPushButton* _eveFacWarTopStats;
        QPushButton* _mapSov;
        QPushButton* _mapFacWarSystems;
        QPushButton* _charSheet;
        QPushButton* _charTraining;
        QPushButton* _charJournal;
        QPushButton* _corpJournal;
        QPushButton* _charWallet;
        QPushButton* _corpWallet;
        QPushButton* _charBalance;
        QPushButton* _corpBalance;
        QPushButton* _corpMembers;
        QPushButton* _charFacWarStats;
        QPushButton* _corpFacWarStats;

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
        void mapFacWarSystems();
        void charSheet();
        void charTraining();
        void charJournal();
        void corpJournal();
        void charWallet();
        void corpWallet();
        void charBalance();
        void corpBalance();
        void corpMembers();
        void charFacWarStats();
        void corpFacWarStats();
        void eveFacWarStats();
        void eveFacWarTopStats();
        void requestComplete( QString id, shared_ptr<QDomDocument> result, QString httpResponse, QDateTime cacheTime );
        void requestFailed( QString id, QString error, QString httpResponse );
};

#endif
