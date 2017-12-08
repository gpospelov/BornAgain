#include "google_test.h"
#include "SessionModel.h"
#include "IntensityDataItem.h"
#include <QTest>

class TestIntensityDataItem : public ::testing::Test
{
public:
    ~TestIntensityDataItem();
};

TestIntensityDataItem::~TestIntensityDataItem() = default;

TEST_F(TestIntensityDataItem, test_lastModified)
{
    SessionModel model("TempModel");
    IntensityDataItem* item
        = dynamic_cast<IntensityDataItem*>(model.insertNewItem(Constants::IntensityDataType));

    QDateTime time = QDateTime::currentDateTime();
    item->setLastModified(time);
    EXPECT_EQ(time, item->lastModified());

    const int nap_time(20);
    QTest::qSleep(nap_time);

    // changing item (file name)
    item->setItemValue(IntensityDataItem::P_FILE_NAME, "name.txt");
    QDateTime time2 = item->lastModified();
    EXPECT_TRUE(time.msecsTo(time2) > nap_time / 2);

    QTest::qSleep(nap_time);

    // changing item (OutputData)
    item->emitDataChanged();
    QDateTime time3 = item->lastModified();
    EXPECT_TRUE(time2.msecsTo(time3) > nap_time / 2);
}
