#ifndef TASKSSORTFILTERPROXYMODEL_H
#define TASKSSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class TasksSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    TasksSortFilterProxyModel(QObject *parent = 0);
    virtual	~TasksSortFilterProxyModel();
    void deleteRow(const QModelIndex &index);
    void changeRow(const QModelIndex &index, QVariant newData);
signals:
    void deleteR(const QModelIndex &index);
    void changeR(const QModelIndex &index, QVariant newData);

};

#endif // TASKSSORTFILTERPROXYMODEL_H
