#include "TasksSortFilterProxyModel.h"
#include "TitleDelegat.h"
#include <QDebug>
#include <QMetaProperty>

TitleDelegat::TitleDelegat(MainTableView *tv, QObject *parent) : QStyledItemDelegate(parent), tableView(tv) {}

void TitleDelegat::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    TasksSortFilterProxyModel* proxyModel = qobject_cast<TasksSortFilterProxyModel*>(model);

    QByteArray n = editor->metaObject()->userProperty().name();
    proxyModel->changeRow(index, editor->property(n));

}
void TitleDelegat::initStyleOption(QStyleOptionViewItem *option,
                         const QModelIndex &index) const
{
    QStyledItemDelegate::initStyleOption(option, index);

    QStyleOptionViewItemV4 *optionV4 =
            qstyleoption_cast<QStyleOptionViewItemV4*>(option);

    if(index.model()->index(index.row(), 1).data().toString() == "complete")
        optionV4->backgroundBrush = QBrush(QColor(192,192,192));
    else
        optionV4->backgroundBrush = QBrush(QColor(248,248,248));
}
