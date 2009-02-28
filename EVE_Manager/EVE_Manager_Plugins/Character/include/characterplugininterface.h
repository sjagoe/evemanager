#ifndef CHARACTERPLUGININTERFACE_H
#define CHARACTERPLUGININTERFACE_H

#include "maininterface.h"

class CharacterPluginInterface: public MainInterface
{
public:
    virtual const QString& getLabel() const = 0;
};

Q_DECLARE_INTERFACE(CharacterPluginInterface, "com.EveManager.Plugin.CharacterPluginInterface/0.1");

#endif // CHARACTERPLUGININTERFACE_H
