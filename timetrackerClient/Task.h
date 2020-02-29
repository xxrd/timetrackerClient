#ifndef TASK_H
#define TASK_H

#include "TimeDelta.h"
#include <QString>
#include <qdatetime.h>
#include <QJsonValue>

class Task
{
public:
    enum TaskTimerStatus
    {
        run = 0,
        stop = 1
    };

    enum TaskStatus
    {
        active = 0,
        complete = 1
    };

    Task();

    Task(QString id,
         QString title,
         QString executor,
         QDateTime startDate,
         QDateTime endDate,
         TimeDelta timerTime,
         TaskTimerStatus timerStatus,
         TaskStatus status);

    QString id;
    QString title;
    QString executor;
    QDateTime startDate;
    QDateTime endDate;
    TimeDelta timerTime;
    TaskTimerStatus timerStatus;
    TaskStatus status;

    static int columnCount();
    static Task fromJson(const QJsonValue& QJsonValue);

};

#endif // TASK_H
