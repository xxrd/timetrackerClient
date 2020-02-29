#ifndef DIGITALCLOCK_H
#define DIGITALCLOCK_H

#include "TasksModel.h"
#include "TasksSortFilterProxyModel.h"
#include <qlabel.h>
#include <QTimer>
#include <qsortfilterproxymodel.h>

class DigitalClock : public QLabel
{
    Q_OBJECT
private:
    QTimer* timer;
    TasksSortFilterProxyModel *model;
    QModelIndex index;
public:
    DigitalClock(TasksSortFilterProxyModel *tm, QModelIndex index, QWidget *parent = nullptr);
    void stop();
    void start();

private slots:
    void showTime();

};

#endif // DIGITALCLOCK_H
