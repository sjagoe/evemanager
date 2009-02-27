#ifndef MAININTERFACE_H
#define MAININTERFACE_H

class QWidget;

class MainInterface
{
public:
    virtual ~MainInterface() {}
    virtual QWidget* getWidget() = 0;
};

Q_DECLARE_INTERFACE(MainInterface, "com.EveManager.Plugin.MainInterface/0.1");

#endif // MAININTERFACE_H
