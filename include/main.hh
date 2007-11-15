#ifndef __MAIN_HH__
#define __MAIN_HH__

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

#include "eveapi.hh"

class Window: public QWidget
{
    Q_OBJECT
    public:
        Window( QWidget* parent = 0 );

    private:
        QPushButton* _eveSkillTree;
        QPushButton* _eveRefTypes;
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

        EveApi* _api;

    private slots:
        void eveSkillTree();
        void eveRefTypes();
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
        void requestComplete( QString id, QDomDocument result, QString httpResponse );
        void requestFailed( QString id, QString error, QString httpResponse );
};

#endif
