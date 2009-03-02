#include "include/tablemodel.h"

TableModel::TableModel(QObject* parent):
        QAbstractTableModel(parent)
{
    this->_columnCount = 0;
}

TableModel::TableModel(const QStringList& header, const QList< QStringList >& data, QObject* parent):
        QAbstractTableModel(parent)
{
    this->_header = header;
    this->_data = data;
    this->_columnCount = this->_header.length();
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return this->_data.length();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return this->_columnCount;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= this->_data.length() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        QStringList row = this->_data.at(index.row());

        if (index.column() >= row.length() || index.column() < 0)
            return QVariant();
        return row.at(index.column());
    }
    return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
    {
        if (section >= this->_columnCount || section < 0)
            return QVariant();
        return this->_header.at(section);
    }
    return QVariant();
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
//    return Qt::ItemIsEnabled;

    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index);
}

QList< QStringList > TableModel::getList()
{
    return this->_data;
}
