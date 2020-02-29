#ifndef TIMERCLOCKDELEGAT_H
#define TIMERCLOCKDELEGAT_H

#include <QStyledItemDelegate>
#include "DigitalClock.h"
#include "MainTableView.h"

class TimerClockDelegat : public QStyledItemDelegate
{
Q_OBJECT
private:
    MainTableView* tableView;
public:
    TimerClockDelegat(MainTableView *tv, QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // TIMERCLOCKDELEGAT_H
