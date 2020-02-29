#ifndef TASKSMODEL_H
#define TASKSMODEL_H

#include "Task.h"
#include <QHash>
#include <QAbstractItemModel>
#include <QDebug>

class TasksModel : public QAbstractTableModel
{
    Q_OBJECT
private:
    QVector<Task> tasksVector;
public:
    enum Role
    {
        TitleRole = Qt::UserRole + 1,
        ExecutorRole,
        StartDateRole,
        EndDateRole,
        TimerTimeRole,
        TimerStatusRole,
        StatusRole,
        IdRole
    };
    QHash<int, QByteArray> roleNames() const;
    QVariant data(const QModelIndex &index, int nRole) const;
    bool setData(const QModelIndex& index, const QVariant& value, int nRole = Qt::EditRole);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int nSection, Qt::Orientation orientation, int nRole) const;
    Qt::ItemFlags flags(const QModelIndex& index) const;
    bool insertRows(int nRow, int nCount, const QModelIndex &parent = QModelIndex());
    bool removeRows(int nRow, int nCount, const QModelIndex &parent = QModelIndex());
    void append(const Task & task);
    void prepend(const Task & task);
};



#endif // TASKSMODEL_H
