#include <QtTest>
#include "SessionModel.h"
#include "IntensityDataItem.h"
#include <QDebug>

class TestIntensityDataItem : public QObject
{
    Q_OBJECT

private slots:
    void test_lastModified();
};

inline void TestIntensityDataItem::test_lastModified()
{
    SessionModel model("TempModel");
    IntensityDataItem* item = dynamic_cast<IntensityDataItem*>(
        model.insertNewItem(Constants::IntensityDataType));

    QDateTime time = QDateTime::currentDateTime();
    item->setLastModified(time);
    QVERIFY(time == item->lastModified());

    const int nap_time(10);
    QTest::qSleep(nap_time);

    // changing item (file name)
    item->setItemValue(IntensityDataItem::P_FILE_NAME, "name.txt");
    QDateTime time2 = item->lastModified();
    QVERIFY(time.msecsTo(time2) >= nap_time);

    QTest::qSleep(nap_time);

    // changing item (OutputData)
    item->emitDataChanged();
    QDateTime time3 = item->lastModified();
    QVERIFY(time2.msecsTo(time3) >= nap_time);
}

