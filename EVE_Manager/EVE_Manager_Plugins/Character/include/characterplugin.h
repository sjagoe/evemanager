#ifndef CHARACTERPLUGIN_H
#define CHARACTERPLUGIN_H

#include <QObject>

#include "maininterface.h"

class CharacterPlugin : public QObject, MainInterface
{
    Q_OBJECT;
    Q_INTERFACES(MainInterface);
public:
    CharacterPlugin();

    virtual QWidget* getWidget();

private:
    QWidget* _widget;
};

#endif // CHARACTERPLUGIN_H
