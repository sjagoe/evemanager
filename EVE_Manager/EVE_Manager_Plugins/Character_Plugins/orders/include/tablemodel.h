#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QStringList>
#include <QVariant>

class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    TableModel(QObject* parent=0);
    TableModel(const QStringList& header, const QList< QStringList >& data, QObject* parent=0);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
//    bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole);
//    bool insertRows(int position, int rows, const QModelIndex &index=QModelIndex());
//    bool removeRows(int position, int rows, const QModelIndex &index=QModelIndex());
    QList< QStringList > getList();

 private:
    QList< QStringList > _data;

    int _columnCount;

    QStringList _header;
};

#endif // TABLEMODEL_H
