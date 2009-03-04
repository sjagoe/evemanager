#ifndef MAININTERFACE_H
#define MAININTERFACE_H

class QWidget;

class MainInterface
{
public:
    virtual ~MainInterface() {}
    virtual void initialise() = 0;
    virtual QWidget* getWidget() = 0;
    virtual void setPluginPath(const QStringList& pluginPath) {}
};

Q_DECLARE_INTERFACE(MainInterface, "com.EveManager.Plugin.MainInterface/0.1");

#endif // MAININTERFACE_H
