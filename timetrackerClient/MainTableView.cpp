#include "MainTableView.h"
#include "BackgroundColorDelegate.h"
#include "MenuDelegat.h"
#include "PlayButtonDelegat.h"
#include "TimerClockDelegat.h"
#include "TitleDelegat.h"
#include "ExecutorDelegat.h"

MainTableView::MainTableView(QWidget *parent) : QTableView(parent) {}

void MainTableView::setup()
{
    setItemDelegate(new BackgroundColorDelegate());
    setItemDelegateForColumn(0,new MenuDelegat(this));
    setItemDelegateForColumn(2,new TitleDelegat(this));
    setItemDelegateForColumn(3,new ExecutorDelegat(this));
    setItemDelegateForColumn(6,new TimerClockDelegat(this));
    setItemDelegateForColumn(7,new PlayButtonDelegat(this));
    for(int i = 0; i < model()->rowCount(); i++) {
        openPersistentEditor(model()->index(i,0));
        openPersistentEditor(model()->index(i,6));
        openPersistentEditor(model()->index(i,7));
    }

    horizontalHeader()->setSectionResizeMode(
        2, QHeaderView::Stretch);

    setColumnWidth(0, 1);
    setColumnWidth(1, 65);
    setColumnWidth(3, 120);
    setColumnWidth(4, 100);
    setColumnWidth(5, 100);
    setColumnWidth(6, 110);
    setColumnWidth(7, 50);

    setSortingEnabled(true);

    hideColumn(8);
    hideColumn(9);
}

void MainTableView::updateView(TasksSortFilterProxyModel* model)
{
    setModel(0);
    setModel(model);
    setup();
}




