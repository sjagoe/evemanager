#include "include/orderswidget.h"

#include "tablemodel.h"

OrdersWidget::OrdersWidget(QWidget* parent):
        QWidget(parent)
{
    this->_ui.setupUi(this);
}

void OrdersWidget::setModels(shared_ptr<TableModel> sellOrderModel, shared_ptr<TableModel> buyOrderModel)
{
    this->_ui.tblSellOrders->setModel(sellOrderModel.get());
    this->_ui.tblBuyOrders->setModel(buyOrderModel.get());
}
