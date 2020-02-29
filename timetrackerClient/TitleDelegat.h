#ifndef TITLEDELEGAT_H
#define TITLEDELEGAT_H

#include "MainTableView.h"
#include <QStyledItemDelegate>

class TitleDelegat : public QStyledItemDelegate
{
Q_OBJECT
private:
    MainTableView* tableView;
public:
    TitleDelegat(MainTableView *tv, QObject *parent = 0);
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void initStyleOption(QStyleOptionViewItem *option,
                         const QModelIndex &index) const;
};

#endif // TITLEDELEGAT_H
