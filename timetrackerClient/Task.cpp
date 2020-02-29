#include "Task.h"

Task::Task() {}

Task::Task(QString id,
           QString title,
           QString executor,
           QDateTime startDate,
           QDateTime endDate,
           TimeDelta timerTime,
           TaskTimerStatus timerStatus,
           TaskStatus status) : id(id), title(title), executor(executor), startDate(startDate),
     endDate(endDate), timerTime(timerTime), timerStatus(timerStatus), status(status) {}

int Task::columnCount() {
    return 10;
}

Task Task::fromJson(const QJsonValue& jsonValue) {
    QDateTime startDateTime = QDateTime::fromString(jsonValue["startDateTime"].toString(), Qt::ISODate).toLocalTime();
    QDateTime endDateTime = QDateTime::fromString(jsonValue["endDateTime"].toString(), Qt::ISODate).toLocalTime();
    TimeDelta timerTime(jsonValue["timerTime"].toString().split(".")[0].toInt());
    Task::TaskTimerStatus timerStatus = Task::TaskTimerStatus::run;
    if(jsonValue["timerStatus"].toString() == "stop") timerStatus = Task::TaskTimerStatus::stop;
    Task::TaskStatus taskStatus = Task::TaskStatus::active;
    if(jsonValue["status"].toString() == "complete") taskStatus = Task::TaskStatus::complete;

    return Task(
        QString::number(jsonValue["pk"].toDouble()),
        jsonValue["title"].toString(),
        jsonValue["executor"].toString(),
        startDateTime,
        endDateTime,
        timerTime,
        timerStatus,
        taskStatus);
}

