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

    virtual void initialise();

    virtual QWidget* getWidget();

    virtual void setPluginPath(const QStringList& pluginPath);

private:

    QStringList _pluginPath;

    QTabWidget* _tabWidget;

    QList<shared_ptr<CharacterPluginInterface> > _plugins;
};

#endif // CHARACTERPLUGIN_H
