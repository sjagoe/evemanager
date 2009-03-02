/********************************************************************************
** Form generated from reading ui file 'orders.ui'
**
** Created: Sun 1. Mar 23:52:39 2009
**      by: Qt User Interface Compiler version 4.5.0-beta1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_ORDERS_H
#define UI_ORDERS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OrdersWidget
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *lblSellOrders;
    QTableView *tblSellOrders;
    QLabel *lblBuyOrders;
    QTableView *tblBuyOrders;

    void setupUi(QWidget *OrdersWidget)
    {
        if (OrdersWidget->objectName().isEmpty())
            OrdersWidget->setObjectName(QString::fromUtf8("OrdersWidget"));
        OrdersWidget->resize(571, 573);
        verticalLayout = new QVBoxLayout(OrdersWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lblSellOrders = new QLabel(OrdersWidget);
        lblSellOrders->setObjectName(QString::fromUtf8("lblSellOrders"));

        verticalLayout->addWidget(lblSellOrders);

        tblSellOrders = new QTableView(OrdersWidget);
        tblSellOrders->setObjectName(QString::fromUtf8("tblSellOrders"));

        verticalLayout->addWidget(tblSellOrders);

        lblBuyOrders = new QLabel(OrdersWidget);
        lblBuyOrders->setObjectName(QString::fromUtf8("lblBuyOrders"));

        verticalLayout->addWidget(lblBuyOrders);

        tblBuyOrders = new QTableView(OrdersWidget);
        tblBuyOrders->setObjectName(QString::fromUtf8("tblBuyOrders"));

        verticalLayout->addWidget(tblBuyOrders);


        retranslateUi(OrdersWidget);

        QMetaObject::connectSlotsByName(OrdersWidget);
    } // setupUi

    void retranslateUi(QWidget *OrdersWidget)
    {
        OrdersWidget->setWindowTitle(QApplication::translate("OrdersWidget", "Form", 0, QApplication::UnicodeUTF8));
        lblSellOrders->setText(QApplication::translate("OrdersWidget", "Sell Orders", 0, QApplication::UnicodeUTF8));
        lblBuyOrders->setText(QApplication::translate("OrdersWidget", "Buy Orders", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(OrdersWidget);
    } // retranslateUi

};

namespace Ui {
    class OrdersWidget: public Ui_OrdersWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ORDERS_H
