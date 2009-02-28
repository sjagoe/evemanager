#include "include/charactersettingsplugin.h"

#include <QtGui>

CharacterSettingsPlugin::CharacterSettingsPlugin()
{
    this->_widget = new QPushButton("Hi there");
    this->_label = "Settings";
}

QWidget* CharacterSettingsPlugin::getWidget()
{
    return this->_widget;
}

const QString& CharacterSettingsPlugin::getLabel() const
{
    return this->_label;
}

Q_EXPORT_PLUGIN2(charactersettingsplugin, CharacterSettingsPlugin);
