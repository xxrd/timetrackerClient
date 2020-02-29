#include "TasksSortFilterProxyModel.h"


TasksSortFilterProxyModel::TasksSortFilterProxyModel(QObject *parent) : QSortFilterProxyModel(parent) {}

TasksSortFilterProxyModel::~TasksSortFilterProxyModel() {}

void TasksSortFilterProxyModel::deleteRow(const QModelIndex &index)
{
    emit deleteR(index);
}

void TasksSortFilterProxyModel::changeRow(const QModelIndex &index, QVariant newData)
{
    emit changeR(index, newData);
}
