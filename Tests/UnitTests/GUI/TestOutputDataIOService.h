#include <QtTest>
#include "ApplicationModels.h"
#include "OutputDataIOService.h"
#include "RealDataItem.h"
#include "JobModel.h"
#include "JobItem.h"
#include "JobItemUtils.h"
#include "IntensityDataItem.h"
#include "OutputDataIOHistory.h"
#include "GUIHelpers.h"
#include <QSignalSpy>
#include <QDebug>

class TestOutputDataIOService : public QObject
{
    Q_OBJECT

private slots:
    void test_nonXMLData();
    void test_OutputDataSaveInfo();
    void test_OutputDataDirHistory();
    void test_OutputDataIOHistory();
};

//! Test methods for retrieving nonXML data.

inline void TestOutputDataIOService::test_nonXMLData()
{
    ApplicationModels models;

    // initial state
    auto dataItems = models.nonXMLData();
    QCOMPARE(dataItems.size(), 0);

    // adding RealDataItem
    SessionItem* realData = models.realDataModel()->insertNewItem(Constants::RealDataType);
    QCOMPARE(models.realDataModel()->nonXMLData().size(), 1);

    // adding JobItem
    SessionItem* jobItem = models.jobModel()->insertNewItem(Constants::JobItemType);
    SessionItem* dataItem = models.jobModel()->insertNewItem(Constants::IntensityDataType,
        jobItem->index(), -1, JobItem::T_OUTPUT);
    QCOMPARE(models.jobModel()->nonXMLData().size(), 1);

    // adding RealDataItem to jobItem
    SessionItem* realData2 = models.jobModel()->insertNewItem(Constants::RealDataType,
        jobItem->index(), -1, JobItem::T_REALDATA);
    QCOMPARE(models.jobModel()->nonXMLData().size(), 2);

    // checking data items of ApplicationModel
    dataItems = models.nonXMLData();
    QCOMPARE(dataItems.size(), 3);
    QCOMPARE(dataItems.indexOf(realData->getItem(RealDataItem::T_INTENSITY_DATA)), 0);
    QCOMPARE(dataItems.indexOf(dataItem), 1);
    QCOMPARE(dataItems.indexOf(realData2->getItem(RealDataItem::T_INTENSITY_DATA)), 2);

    // checking data items of OutputDataIOService
    OutputDataIOService service(&models);
    QCOMPARE(service.dataItems().size(), 3);
}

//! Tests OutputDataSaveInfo class intended for storing info about the last save.

inline void TestOutputDataIOService::test_OutputDataSaveInfo()
{
    SessionModel model("TempModel");
    IntensityDataItem* item = dynamic_cast<IntensityDataItem*>(
        model.insertNewItem(Constants::IntensityDataType));

    item->setLastModified(QDateTime::currentDateTime());

    const int nap_time(10);
    QTest::qSleep(nap_time);

    OutputDataSaveInfo info = OutputDataSaveInfo::createSaved(item);
    QVERIFY(info.wasModifiedSinceLastSave() == false);

    QTest::qSleep(nap_time);
    item->setLastModified(QDateTime::currentDateTime());
    QVERIFY(info.wasModifiedSinceLastSave() == true);

}

//! Tests OutputDataDirHistory class intended for storing save history of several
//! IntensityDataItems in a directory.

inline void TestOutputDataIOService::test_OutputDataDirHistory()
{
    SessionModel model("TempModel");
    IntensityDataItem* item1 = dynamic_cast<IntensityDataItem*>(
        model.insertNewItem(Constants::IntensityDataType));

    IntensityDataItem* item2 = dynamic_cast<IntensityDataItem*>(
        model.insertNewItem(Constants::IntensityDataType));

    item1->setLastModified(QDateTime::currentDateTime());
    item2->setLastModified(QDateTime::currentDateTime());

    // empty history
    OutputDataDirHistory history;
    QVERIFY(history.contains(item1) == false);
    // non-existing item is treated as modified
    QVERIFY(history.wasModifiedSinceLastSave(item1) == true);

    // Saving item in a history
    history.markAsSaved(item1);
    history.markAsSaved(item2);

    QVERIFY(history.contains(item1) == true);
    QVERIFY(history.contains(item2) == true);
    QVERIFY(history.wasModifiedSinceLastSave(item1) == false);
    QVERIFY(history.wasModifiedSinceLastSave(item2) == false);

    // Attempt to save same item second time
    QVERIFY_EXCEPTION_THROWN(history.markAsSaved(item1), GUIHelpers::Error);

    // Modifying item
    QTest::qSleep(10);
    item1->setLastModified(QDateTime::currentDateTime());

    QVERIFY(history.wasModifiedSinceLastSave(item1) == true);
    QVERIFY(history.wasModifiedSinceLastSave(item2) == false);
}

inline void TestOutputDataIOService::test_OutputDataIOHistory()
{
    SessionModel model("TempModel");
    IntensityDataItem* item1 = dynamic_cast<IntensityDataItem*>(
        model.insertNewItem(Constants::IntensityDataType));

    IntensityDataItem* item2 = dynamic_cast<IntensityDataItem*>(
        model.insertNewItem(Constants::IntensityDataType));

    item1->setLastModified(QDateTime::currentDateTime());
    item2->setLastModified(QDateTime::currentDateTime());

    OutputDataDirHistory dirHistory1;
    dirHistory1.markAsSaved(item1);
    dirHistory1.markAsSaved(item2);

    OutputDataDirHistory dirHistory2;
    dirHistory2.markAsSaved(item1);

    // Modifying item
    QTest::qSleep(10);
    item1->setLastModified(QDateTime::currentDateTime());

    // Creating two histories
    OutputDataIOHistory history;
    history.setHistory("dir1", dirHistory1);
    history.setHistory("dir2", dirHistory2);

    QVERIFY(history.wasModifiedSinceLastSave("dir1", item1) == true);
    QVERIFY(history.wasModifiedSinceLastSave("dir2", item1) == true);

    QVERIFY(history.wasModifiedSinceLastSave("dir1", item2) == false);
    QVERIFY(history.wasModifiedSinceLastSave("dir2", item2) == true); // since item2 doesn't exist

    // asking info for some non-existing directory
    QVERIFY_EXCEPTION_THROWN(history.wasModifiedSinceLastSave("dir3", item1), GUIHelpers::Error);

}


