#include "ExecutorDelegat.h"
#include "TasksSortFilterProxyModel.h"
#include <QDebug>
#include <QMetaProperty>

ExecutorDelegat::ExecutorDelegat(MainTableView *tv, QObject *parent) : QStyledItemDelegate(parent), tableView(tv) {}

void ExecutorDelegat::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    TasksSortFilterProxyModel* proxyModel = qobject_cast<TasksSortFilterProxyModel*>(model);

    QByteArray n = editor->metaObject()->userProperty().name();
    proxyModel->changeRow(index, editor->property(n));

}
void ExecutorDelegat::initStyleOption(QStyleOptionViewItem *option,
                         const QModelIndex &index) const
{
    QStyledItemDelegate::initStyleOption(option, index);

    QStyleOptionViewItemV4 *optionV4 =
            qstyleoption_cast<QStyleOptionViewItemV4*>(option);

    if(index.model()->index(index.row(), 1).data().toString() == "complete")
        optionV4->backgroundBrush = QBrush(QColor(192,192,192));
    else
        optionV4->backgroundBrush = QBrush(QColor(242,242,242));
}
