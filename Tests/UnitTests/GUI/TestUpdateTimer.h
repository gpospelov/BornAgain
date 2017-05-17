#include <QtTest>
#include "UpdateTimer.h"
#include <QSignalSpy>
#include <QDebug>

class TestUpdateTimer : public QObject
{
    Q_OBJECT

private slots:
    void test_updateTimerShort();
};

inline void TestUpdateTimer::test_updateTimerShort()
{
    const int timer_interval(100);
    UpdateTimer timer(timer_interval);

    QSignalSpy spy(&timer, SIGNAL(timeToUpdate()));

    for (int i = 0; i < 10; ++i)
        timer.scheduleUpdate();

    // Checks that after time bigger than timer interval, we have a valid signal
    QVERIFY(spy.wait(timer_interval * 3));
    QCOMPARE(spy.count(), 1);

    // once again
    timer.scheduleUpdate();
    QVERIFY(spy.wait(timer_interval * 3));
    QCOMPARE(spy.count(), 2);

    // Checks that after time smaller than timer interval, we have no signals
    for (int i = 0; i < 10; ++i)
        timer.scheduleUpdate();

    QVERIFY(spy.wait(timer_interval / 2) == false);
    QCOMPARE(spy.count(), 2);
}
