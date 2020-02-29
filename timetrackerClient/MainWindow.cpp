#include "MainWindow.h"
#include "BackgroundColorDelegate.cpp"
#include "LoggingCategories.h"
#include "DigitalClock.h"
#include "config.h"

MainWindow::MainWindow(QWidget* parent) : QWidget(parent) {}

void MainWindow::addTask(
        MainTableView* tableView,
        TasksModel *model,
        TasksSortFilterProxyModel *proxyModel,
        QLineEdit *editMessage,
        QLineEdit *executorName,
        NetworkManager* networkManager)
{

    QJsonObject json;
    json.insert("title", editMessage->text());
    json.insert("executor", executorName->text());
    QJsonDocument jsonBody(json);

    editMessage->clear();
    executorName->clear();

    networkManager->sendPost(config::QUERY_STRING + "/tasks", jsonBody, [model, tableView, proxyModel](QNetworkReply* reply) {

        QByteArray responseData = reply->readAll();
        QJsonDocument jsonDocument = QJsonDocument::fromJson(responseData);

        QVariant statusCode = reply->attribute( QNetworkRequest::HttpStatusCodeAttribute );
        int status = statusCode.toInt();
        if(status != 200) {
                qCritical(logCritical()) << "status: " + QString::number(status) + " detail: " + jsonDocument["detail"].toString();
                return;
        }
        model->append(Task::fromJson(QJsonValue(jsonDocument.object())));

        tableView->sortByColumn(4, Qt::DescendingOrder);
        tableView->updateView(proxyModel);

    });
}

void MainWindow::setTasksCount(TasksSortFilterProxyModel *proxyModel, QLabel *tasksCount)
{
    tasksCount->setText("tasks count: " + QString::number(proxyModel->rowCount()));
}

void MainWindow::setup(NetworkManager* networkManager) {
    auto *layoutMain = new QVBoxLayout(this);
    auto *groupAdd = new QGroupBox(tr("Add new task"), this);
    auto *layoutToolbar = new QHBoxLayout(groupAdd);
    auto *editMessage = new QLineEdit(this);
    auto *executorName = new QLineEdit(this);
    auto *btnPost = new QPushButton(tr("Add"), this);
    auto *groupFooter = new QGroupBox(this);
    auto *layoutFooter = new QHBoxLayout(groupFooter);
    auto *tasksCount = new QLabel();

    editMessage->setPlaceholderText(tr("Task title..."));
    executorName->setPlaceholderText(tr("Executor name..."));

    layoutFooter->addWidget(tasksCount);

    layoutToolbar->addWidget(editMessage);
    layoutToolbar->addWidget(executorName);
    layoutToolbar->addWidget(btnPost);

    layoutMain->addWidget(groupAdd);

    TasksModel* model = new TasksModel();

    networkManager->sendGet(config::QUERY_STRING + "/tasks", [model](QNetworkReply* reply) {
            QByteArray responseData = reply->readAll();
            QJsonDocument jsonDocument = QJsonDocument::fromJson(responseData);
            for(int i = 0; i < jsonDocument.array().size(); i++) {
                model->append(Task::fromJson(jsonDocument[i]));
            }
    });

    TasksSortFilterProxyModel *proxyModel = new TasksSortFilterProxyModel(model);
    proxyModel->setSourceModel(model);

    MainTableView* tableView = new MainTableView(this);
    tableView->setModel(proxyModel);
    tableView->setup();
    tableView->sortByColumn(4, Qt::DescendingOrder);

    layoutMain->addWidget(tableView);
    layoutMain->addWidget(groupFooter);

    resize(840, 480);

    QHeaderView * headerView = tableView->horizontalHeader();



    connect(btnPost, &QPushButton::clicked, [this, tableView, model, editMessage, executorName, proxyModel, networkManager]() {
        addTask(tableView, model, proxyModel, editMessage, executorName, networkManager);
    });

    connect(headerView, &QHeaderView::sectionClicked, [tableView, proxyModel]() {
        tableView->updateView(proxyModel);
    });

    connect(proxyModel, &QAbstractTableModel::rowsRemoved, [this, proxyModel, tasksCount, tableView]() {
        tableView->updateView(proxyModel);
        setTasksCount(proxyModel, tasksCount);
    });

    connect(proxyModel, &QAbstractTableModel::rowsInserted, [this, proxyModel, tasksCount, tableView]() {
        tableView->updateView(proxyModel);
        setTasksCount(proxyModel, tasksCount);
    });


    connect(proxyModel, &TasksSortFilterProxyModel::changeR, [proxyModel, tableView, networkManager](const QModelIndex &index, QVariant newData) {

        QString field;
        if(index.column() == 2) field = "title";
        else if(index.column() == 3) field = "executor";
        else if(index.column() == 0) field = "status";
        else if(index.column() == 7) field = "timerStatus";
        else return;

        QJsonObject json;
        json.insert(field, newData.toString());
        QJsonDocument jsonBody(json);

        networkManager->sendPut(config::QUERY_STRING + "/tasks/" + proxyModel->index(index.row(), 9).data().toString(),
                                jsonBody, [proxyModel, index, field, newData, tableView](QNetworkReply* reply) {
            QByteArray responseData = reply->readAll();
            QJsonDocument jsonDocument = QJsonDocument::fromJson(responseData);

            QVariant statusCode = reply->attribute( QNetworkRequest::HttpStatusCodeAttribute );
            int status = statusCode.toInt();
            if(status != 200) {
                    qCritical(logCritical()) << "status: " + QString::number(status) + " detail: " + jsonDocument["detail"].toString();
                    return;
            }

            if(field == "status") {
                if(newData.toString() == "complete") {
                    if(proxyModel->index(index.row(), 8).data().toInt() == Task::TaskTimerStatus::run) {
                        qobject_cast <DigitalClock *>(tableView->indexWidget(proxyModel->index(index.row(),6)))->stop();
                        qobject_cast <QPushButton *>(tableView->indexWidget(proxyModel->index(index.row(),7)))->setText("&start");

                        proxyModel->setData(proxyModel->index(index.row(), 8), Task::TaskTimerStatus::stop);
                    }

                    proxyModel->setData(proxyModel->index(index.row(), 1), Task::TaskStatus::complete);
                    proxyModel->setData(proxyModel->index(index.row(), 5), QDateTime::currentDateTime());
                    tableView->updateView(proxyModel);
                }
                else if(newData.toString() == "active") {
                    proxyModel->setData(proxyModel->index(index.row(), 1), Task::TaskStatus::active);
                    proxyModel->setData(proxyModel->index(index.row(), 5), QDateTime());
                    tableView->updateView(proxyModel);
                }
            }
            else if (field == "timerStatus") {
                if(newData.toString() == "stop") {
                    qobject_cast <DigitalClock *>(tableView->indexWidget(proxyModel->index(index.row(),6)))->stop();
                    qobject_cast <QPushButton *>(tableView->indexWidget(proxyModel->index(index.row(),7)))->setText("&start");
                    proxyModel->setData(proxyModel->index(index.row(), 8), Task::TaskTimerStatus::stop);
                }
                else if(newData.toString() == "run") {
                    qobject_cast <DigitalClock *>(tableView->indexWidget(proxyModel->index(index.row(),6)))->start();
                    qobject_cast <QPushButton *>(tableView->indexWidget(proxyModel->index(index.row(),7)))->setText("&stop");
                    proxyModel->setData(proxyModel->index(index.row(), 8), Task::TaskTimerStatus::run);
                }
            }

            proxyModel->setData(index, jsonDocument[field].toString());

        } );

    });

    connect(proxyModel, &TasksSortFilterProxyModel::deleteR, [proxyModel, networkManager](const QModelIndex &index) {

        networkManager->sendDelete(config::QUERY_STRING + "/tasks/" + proxyModel->index(index.row(), 9).data().toString(),
                                [proxyModel, index](QNetworkReply* reply) {

            QByteArray responseData = reply->readAll();
            QJsonDocument jsonDocument = QJsonDocument::fromJson(responseData);

            QVariant statusCode = reply->attribute( QNetworkRequest::HttpStatusCodeAttribute );
            int status = statusCode.toInt();
            if(status < 200 && status >= 300) {
                    qCritical(logCritical()) << "status: " + QString::number(status) + " detail: " + jsonDocument["detail"].toString();
                    return;
            }
            proxyModel->removeRow(index.row());

        });

    });

}
