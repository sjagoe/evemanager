#ifndef ORDERSPLUGIN_H
#define ORDERSPLUGIN_H

#include <QObject>
#include <QString>

#include "characterplugininterface.h"

#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

class OrdersWidget;

class TableModel;

class OrdersPlugin : public QObject, CharacterPluginInterface
{
    Q_OBJECT;
    Q_INTERFACES(CharacterPluginInterface);
public:
    OrdersPlugin();
    virtual QWidget* getWidget();
    virtual const QString& getLabel() const;
    virtual void initialise() {}

private:
    OrdersWidget* _widget;

    QString _label;

    shared_ptr<TableModel> _mdlSellOrders;
    shared_ptr<TableModel> _mdlBuyOrders;
};

#endif // ORDERSPLUGIN_H
