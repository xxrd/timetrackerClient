#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "MainTableView.h"
#include "NetworkManager.h"
#include "TasksModel.h"
#include "TasksSortFilterProxyModel.h"
#include <QtWidgets>
#include <qsortfilterproxymodel.h>

class MainWindow : public QWidget {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    void addTask(
            MainTableView *tableView,
            TasksModel *model,
            TasksSortFilterProxyModel *proxyModel,
            QLineEdit *editMessage,
            QLineEdit *executorName,
            NetworkManager* networkManager);
    void setTasksCount(TasksSortFilterProxyModel *proxyModel, QLabel *tasksCount);
    void setup(NetworkManager* networkManager);
};

#endif // MAINWINDOW_H
