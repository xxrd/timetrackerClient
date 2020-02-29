#ifndef DELEGAT_H
#define DELEGAT_H

#include "MainTableView.h"
#include "DigitalClock.h"
#include "MainTableView.h"
#include <QtWidgets>
#include <qstyleditemdelegate.h>
#include "NetworkManager.h"

class MenuDelegat : public QStyledItemDelegate
{
Q_OBJECT
private:
    MainTableView* tableView;
public:
    MenuDelegat(MainTableView *tv, QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

};

#endif // DELEGAT_H
