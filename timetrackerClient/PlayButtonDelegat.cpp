#include "PlayButtonDelegat.h"
#include "DigitalClock.h"

PlayButtonDelegat::PlayButtonDelegat(MainTableView* tv, QObject *parent) : QStyledItemDelegate(parent), tableView(tv) {}

QWidget* PlayButtonDelegat::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {

    QPushButton *button = new QPushButton("&start", parent);

    TasksSortFilterProxyModel* proxyModel = qobject_cast <TasksSortFilterProxyModel *> (tableView->model());

    if(proxyModel->index(index.row(), 8).data().toInt() == Task::TaskTimerStatus::run) {
        button->setText("&stop");
    } else if(proxyModel->index(index.row(), 8).data().toInt() == Task::TaskTimerStatus::stop) {
        button->setText("&start");
    }

    connect(button, &QPushButton::clicked, [proxyModel, index]() {
        if(proxyModel->index(index.row(), 1).data().toString() == "complete") {
            return;
        }

        if(proxyModel->index(index.row(), 8).data().toInt() == Task::TaskTimerStatus::run) {

            proxyModel->changeRow(index, "stop");
            return;
        } else if(proxyModel->index(index.row(), 8).data().toInt() == Task::TaskTimerStatus::stop) {

            proxyModel->changeRow(index, "run");
            return;
        }
    });

    return button;
}

void PlayButtonDelegat::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {}
