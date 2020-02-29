#include "TimerClockDelegat.h"


TimerClockDelegat::TimerClockDelegat(MainTableView* tv, QObject *parent) : QStyledItemDelegate(parent), tableView(tv) {}

QWidget* TimerClockDelegat::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {

    TasksSortFilterProxyModel* proxyModel = qobject_cast <TasksSortFilterProxyModel *> (tableView->model());

    DigitalClock* clock = new DigitalClock(proxyModel, index, parent);

    if(proxyModel->data(proxyModel->index(index.row(), 8)).toInt() == Task::TaskTimerStatus::stop) {
        clock->stop();
    }
    return clock;
}

void TimerClockDelegat::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {}
