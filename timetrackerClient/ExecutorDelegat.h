#ifndef EXECUTORDELEGAT_H
#define EXECUTORDELEGAT_H

#include "MainTableView.h"
#include <QStyledItemDelegate>

class ExecutorDelegat : public QStyledItemDelegate
{
Q_OBJECT
private:
    MainTableView* tableView;
public:
    ExecutorDelegat(MainTableView *tv, QObject *parent = 0);
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void initStyleOption(QStyleOptionViewItem *option,
                         const QModelIndex &index) const;
};
#endif // EXECUTORDELEGAT_H
