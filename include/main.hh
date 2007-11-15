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
        Window( QWidget* parent = 0 );;

    private:
        QPushButton* _btn;

        EveApi _api;

    private slots:
        void run();
        void requestComplete( QString id, QDomDocument result, QString httpResponse );
        void requestFailed( QString id, QString error, QString httpResponse );
};

#endif
