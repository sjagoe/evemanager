/********************************************************************************
** Form generated from reading ui file 'orders.ui'
**
** Created: Wed 4. Mar 22:26:23 2009
**      by: Qt User Interface Compiler version 4.5.0
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
#include <QtGui/QSplitter>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OrdersWidget
{
public:
    QVBoxLayout *verticalLayout_3;
    QSplitter *splitter;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QLabel *lblSellOrders;
    QTableView *tblSellOrders;
    QWidget *widget1;
    QVBoxLayout *verticalLayout;
    QLabel *lblBuyOrders;
    QTableView *tblBuyOrders;

    void setupUi(QWidget *OrdersWidget)
    {
        if (OrdersWidget->objectName().isEmpty())
            OrdersWidget->setObjectName(QString::fromUtf8("OrdersWidget"));
        OrdersWidget->resize(584, 681);
        verticalLayout_3 = new QVBoxLayout(OrdersWidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        splitter = new QSplitter(OrdersWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        widget = new QWidget(splitter);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        lblSellOrders = new QLabel(widget);
        lblSellOrders->setObjectName(QString::fromUtf8("lblSellOrders"));

        verticalLayout_2->addWidget(lblSellOrders);

        tblSellOrders = new QTableView(widget);
        tblSellOrders->setObjectName(QString::fromUtf8("tblSellOrders"));

        verticalLayout_2->addWidget(tblSellOrders);

        splitter->addWidget(widget);
        widget1 = new QWidget(splitter);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        verticalLayout = new QVBoxLayout(widget1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lblBuyOrders = new QLabel(widget1);
        lblBuyOrders->setObjectName(QString::fromUtf8("lblBuyOrders"));

        verticalLayout->addWidget(lblBuyOrders);

        tblBuyOrders = new QTableView(widget1);
        tblBuyOrders->setObjectName(QString::fromUtf8("tblBuyOrders"));

        verticalLayout->addWidget(tblBuyOrders);

        splitter->addWidget(widget1);

        verticalLayout_3->addWidget(splitter);


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
