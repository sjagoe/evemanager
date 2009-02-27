#ifndef EVEMANAGERWINDOW_H
#define EVEMANAGERWINDOW_H

#include <QMainWindow>

#include "maininterface.h"

class EveManagerWindow : public QMainWindow
{
    Q_OBJECT;
public:
    EveManagerWindow();

private:
    bool loadPlugin();

    MainInterface* _interface;
};

#endif // EVEMANAGERWINDOW_H
