#include "include/characterplugin.h"

#include <QtGui>
#include <QPushButton>

CharacterPlugin::CharacterPlugin()
{
    this->_widget = new QPushButton("Hello World!");
}


QWidget* CharacterPlugin::getWidget()
{
    return this->_widget;
}

Q_EXPORT_PLUGIN2(characterplugin, CharacterPlugin);
