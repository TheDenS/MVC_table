#include "mylistmodel.h"
#include <QDebug>


myListModel::myListModel(QObject *parent)
{
    for (int i =0; i<10; i++)
    {
        vector_1<<QPoint(i*2,i*3);
    }
    copy = false;
}

int myListModel::rowCount(const QModelIndex &index) const
{
    return vector_1.count();
}

int myListModel::columnCount(const QModelIndex &index) const
{
    return 2;
}

bool myListModel::removeRows(int row, int count, const QModelIndex &index)
{
    beginRemoveRows(QModelIndex(), row, row + count - 1);
    for (auto i = 0; i < count; ++i)
        vector_1.remove(index.row());
    endRemoveRows();
    return true;
}

bool myListModel::insertRows(int row, int count, const QModelIndex &index)
{
    if(row<0)
    {
        beginInsertRows(QModelIndex(), vector_1.count(), vector_1.count() + count - 1);
    }
    else
    {
        beginInsertRows(QModelIndex(), row, row + count - 1);
    }

    for (auto i = 0; i < count; ++i)
    {   if(row<0)
            vector_1.append(buff);
        else
            vector_1.insert(row,buff);
    }
    endInsertRows();
    return true;
}

bool myListModel::copyData(const QModelIndex &index)
{
    buff = vector_1.at(index.row());
    copy = true;
    return true;
}

bool myListModel::isCopied(const QModelIndex &index = QModelIndex())
{
    if(copy)
        return true;
    else
        return false;
}

QVariant myListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();


    QPoint value = vector_1.at(index.row());
    switch (role){
    case Qt::DisplayRole:
    case Qt::EditRole:
        if(index.column()==0)
        {
            return value.x();
        }
        else
        {
            if(index.column()==1)
                return value.y();
            else {
                return value;
            }
        }

    case Qt::TextAlignmentRole:
        return Qt::AlignCenter;

    case Qt::FontRole:
        return QFont("Times New Roman", 12, QFont::Bold);
    default:
        return QVariant();
    }
}

bool myListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
        vector_1.replace(index.row(),value.toPoint());
    return true;

}

Qt::ItemFlags myListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

QVariant myListModel::headerData(int section, Qt::Orientation orientation, int role)
const
{

    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return tr("X");
        case 1:
            return tr("Y");
        default:
            return QVariant();
        }
    }
    return QVariant();
};

