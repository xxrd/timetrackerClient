#ifndef TIMEDELTA_H
#define TIMEDELTA_H

#include <QMetaType>
#include <QDebug>

class TimeDelta {
private:
    int secs;

public:
    TimeDelta() = default;
    TimeDelta(int s);
    TimeDelta(const TimeDelta &) = default;
    TimeDelta &operator=(const TimeDelta &) = default;

    int seconds() const;
    int minutes() const;
    int hours() const;
    int days() const;
    void addSecs(int s);

    friend QDebug operator<<(QDebug stream, const TimeDelta& td);
    operator QString() const;

};

Q_DECLARE_METATYPE(TimeDelta);

#endif // TIMEDELTA_H
