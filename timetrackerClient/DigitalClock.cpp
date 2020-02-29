#include "DigitalClock.h"
#include "TimeDelta.h"
#include <QTime>
#include <QFont>

DigitalClock::DigitalClock(TasksSortFilterProxyModel *tm, QModelIndex index, QWidget *parent)
    : QLabel(parent), model(tm), index(index)
{
    setStyleSheet("QLabel {  background-color : #595959; color : #fff; font-weight: bold; font-size:12px;   }");
    setAlignment(Qt::AlignCenter);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &DigitalClock::showTime);
    timer->start(1000);

    showTime();
}

void DigitalClock::showTime()
{
    TimeDelta timerTime = qvariant_cast<TimeDelta>(model->index(index.row(), 6).data());
    if(model->index(index.row(), 8).data().toInt() == Task::TaskTimerStatus::run) {
        timerTime.addSecs(1);
        model->setData(model->index(index.row(), 6), QVariant::fromValue<TimeDelta>(timerTime));
    }
    setText(timerTime);
}

void DigitalClock::stop()
{
    timer->stop();
}
void DigitalClock::start()
{
    timer->start(1000);
}
