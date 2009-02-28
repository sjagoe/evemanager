#ifndef CHARACTERSETTINGSPLUGIN_H
#define CHARACTERSETTINGSPLUGIN_H

#include <QObject>
#include <QPushButton>
#include <QString>

#include "characterplugininterface.h"

class CharacterSettingsPlugin : public QObject, CharacterPluginInterface
{
    Q_OBJECT;
    Q_INTERFACES(CharacterPluginInterface);
public:
    CharacterSettingsPlugin();
    virtual QWidget* getWidget();
    virtual const QString& getLabel() const;

private:
    QPushButton* _widget;
    QString _label;
};

#endif // CHARACTERSETTINGSPLUGIN_H
