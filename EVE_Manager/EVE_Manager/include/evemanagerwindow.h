#ifndef EVEMANAGERWINDOW_H
#define EVEMANAGERWINDOW_H

#include <QMainWindow>

#include "maininterface.h"

#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

class EveManagerWindow : public QMainWindow
{
    Q_OBJECT;
public:
    EveManagerWindow();

private:

    shared_ptr<MainInterface> _interface;
};

#endif // EVEMANAGERWINDOW_H
