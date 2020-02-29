#include "MenuDelegat.h"
#include "TasksSortFilterProxyModel.h"

MenuDelegat::MenuDelegat(MainTableView* tv, QObject *parent) : QStyledItemDelegate(parent), tableView(tv) {}

QWidget* MenuDelegat::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {

    TasksSortFilterProxyModel* proxyModel = qobject_cast <TasksSortFilterProxyModel *> (tableView->model());

    QMenuBar* pmbr = new QMenuBar(parent);
    QMenu* pmn = new QMenu("...");

    pmn->addAction("&complete", [index, proxyModel]() {
        if(proxyModel->index(index.row(), 1).data().toString() == "complete") {
            return;
        }
        proxyModel->changeRow(index, "complete");

    });

    pmn->addAction("&renew", [proxyModel, index]() {
        if(proxyModel->index(index.row(), 1).data().toString() == "active") {
            return;
        }
        proxyModel->changeRow(index, "active");

    });

    pmn->addAction("&delete", [proxyModel, index]() {
        proxyModel->deleteRow(index);

    });

    pmbr->addMenu(pmn);
    return pmbr;
}
