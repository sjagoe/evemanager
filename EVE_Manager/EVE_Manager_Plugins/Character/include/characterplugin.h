#ifndef CHARACTERPLUGIN_H
#define CHARACTERPLUGIN_H

#include <QList>
#include <QObject>
#include <QTabWidget>

#include <boost/shared_ptr.hpp>

#include "maininterface.h"

#include "characterplugininterface.h"

using boost::shared_ptr;

class CharacterPlugin : public QObject, MainInterface
{
    Q_OBJECT;
    Q_INTERFACES(MainInterface);
public:
    CharacterPlugin();

    virtual QWidget* getWidget();

private:
    bool _loadPlugins();

    QTabWidget* _tabWidget;

    QList<shared_ptr<CharacterPluginInterface> > _plugins;
};

#endif // CHARACTERPLUGIN_H
