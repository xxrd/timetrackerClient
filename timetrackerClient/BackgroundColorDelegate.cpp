#include "BackgroundColorDelegate.h"

BackgroundColorDelegate::BackgroundColorDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

void BackgroundColorDelegate::initStyleOption(QStyleOptionViewItem *option,
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

