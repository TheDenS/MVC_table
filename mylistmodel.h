#ifndef QTABLEMODEL_H
#define QTABLEMODEL_H

#include <QObject>
#include <QSize>
#include <QBrush>
#include <QFont>
#include <QVector>
#include <QAbstractListModel>


class myListModel : public QAbstractListModel
{
public:
    explicit myListModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    int columnCount(const QModelIndex &) const;

    bool removeRows(int row, int count,const QModelIndex &index);
    bool insertRows(int row,int count, const QModelIndex &index);

    bool copyData(const QModelIndex &index);
    bool isCopied(const QModelIndex &index);

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex & index) const;
    QVariant headerData( int section, Qt::Orientation orientation,int role) const;

private:
    QVector<QPoint> vector_1;
    QPoint buff;
    bool copy;
signals:

public slots:
};

#endif // QTABLEMODEL_H
