#ifndef PLAYBUTTONDELEGAT_H
#define PLAYBUTTONDELEGAT_H

#include "MainTableView.h"
#include <qstyleditemdelegate.h>
#include <QtWidgets>

class PlayButtonDelegat : public QStyledItemDelegate
{
Q_OBJECT
private:
    MainTableView *tableView;
public:
    PlayButtonDelegat(MainTableView *tv, QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};


#endif // PLAYBUTTONDELEGAT_H
