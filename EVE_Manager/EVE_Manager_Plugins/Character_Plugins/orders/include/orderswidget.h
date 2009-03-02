#ifndef ORDERSWIDGET_H
#define ORDERSWIDGET_H

#include <QWidget>

#include "ui_orders.h"

#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

class TableModel;

class OrdersWidget : public QWidget
{
    Q_OBJECT
public:
    OrdersWidget(QWidget* parent=0);

    void setModels(shared_ptr<TableModel> sellOrderModel, shared_ptr<TableModel> buyOrderModel);

private:
    Ui::OrdersWidget _ui;
};

#endif // ORDERSWIDGET_H
