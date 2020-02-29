#include "TimeDelta.h"

TimeDelta::TimeDelta(int s) : secs(s) {}

int TimeDelta::seconds() const { return secs - (minutes() * 60 + hours() * 60 * 60 + days() * 24 * 60 * 60); }

int TimeDelta::minutes() const { return secs / 60 - (hours() * 60 + days() * 24 * 60); }

int TimeDelta::hours() const { return secs / 60 / 60 - days() * 24; }

int TimeDelta::days() const { return secs / 60 / 60 / 24; }

void TimeDelta::addSecs(int s) { secs += s; }

QDebug operator<<(QDebug stream, const TimeDelta& dt) {
    if(dt.days() > 0) stream << dt.days();
    stream << dt.hours() << ":" << dt.minutes() << ":" << dt.seconds();
    return stream;
}

TimeDelta::operator QString() const {
    QString str;
    if(days() > 0) str = QString::number(days()) + " ";
    str += QString::number(hours()) + ":" + QString::number(minutes()) + ":" + QString::number(seconds());
    return str;
}
