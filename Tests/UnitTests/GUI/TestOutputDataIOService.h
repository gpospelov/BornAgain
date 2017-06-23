#include <QtTest>
#include <memory>
#include "ApplicationModels.h"
#include "OutputDataIOService.h"
#include "RealDataItem.h"
#include "JobModel.h"
#include "JobItem.h"
#include "JobItemUtils.h"
#include "IntensityDataItem.h"
#include "OutputDataIOHistory.h"
#include "GUIHelpers.h"
#include "OutputData.h"
#include "ProjectUtils.h"
#include "IntensityDataIOFactory.h"
#include "IntensityDataFunctions.h"
#include <QSignalSpy>
#include <QDebug>

namespace {
const int nxsize = 5;
const int nysize = 10;
}

class TestOutputDataIOService : public QObject
{
    Q_OBJECT

private:

    //! Helper function to create test OutputData.
    std::unique_ptr<OutputData<double>> createData(double value = 0.0)
    {
        std::unique_ptr<OutputData<double>> result(new OutputData<double>());
        result->addAxis("x", nxsize, -1.0, 1.0);
        result->addAxis("y", nysize, 0.0, 2.0);
        result->setAllTo(value);
        return result;
    }

    //! Helper function to create test RealData
    RealDataItem* createRealData(const QString& name, ApplicationModels& models, double value = 0.0)
    {
        RealDataItem* result = dynamic_cast<RealDataItem*>(
            models.realDataModel()->insertNewItem(Constants::RealDataType));
        result->intensityDataItem()->setOutputData(createData(value).release());
        result->setItemValue(SessionItem::P_NAME, name);
        return result;
    }

    //! Helper function to test if data are the same.
    bool isTheSame(const OutputData<double>&data1, const OutputData<double>& data2)
    {
        double diff = IntensityDataFunctions::getRelativeDifference(data1, data2);
        return diff < 1e-10;
    }

    //! Helper function to check if file on disk represents same data.
    bool isTheSame(const QString& fileName, const OutputData<double>& data)
    {
        std::unique_ptr<OutputData<double>> dataOnDisk(
            IntensityDataIOFactory::readOutputData(fileName.toStdString()));
        return isTheSame(*dataOnDisk, data);
    }

private slots:
    void test_nonXMLData();
    void test_OutputDataSaveInfo();
    void test_OutputDataDirHistory();
    void test_OutputDataIOHistory();
    void test_OutputDataIOService();
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

//! Tests OutputDataIOHistory class (save info for several independent directories).

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

//! Testing saving abilities of OutputDataIOService class.

inline void TestOutputDataIOService::test_OutputDataIOService()
{
    const double value1(1.0), value2(2.0), value3(3.0);

    ApplicationModels models;
    RealDataItem* realData1 = createRealData("data1", models, value1);
    RealDataItem* realData2 = createRealData("data2", models, value2);

    const QString projectDir("test_OutputDataIOService");
    GUIHelpers::createSubdir(".", projectDir);

    // Saving first time
    OutputDataIOService service(&models);
    service.save(projectDir);
    QTest::qSleep(10);

    // Checking existance of data on disk
    QString fname1 = "./" + projectDir + "/" + "realdata_data1_0.int.gz";
    QString fname2 = "./" + projectDir + "/" + "realdata_data2_0.int.gz";
    QVERIFY(ProjectUtils::exists(fname1));
    QVERIFY(ProjectUtils::exists(fname2));

    // Reading data from disk, checking it is the same
    std::unique_ptr<OutputData<double>> dataOnDisk1(
        IntensityDataIOFactory::readOutputData(fname1.toStdString()));
    std::unique_ptr<OutputData<double>> dataOnDisk2(
        IntensityDataIOFactory::readOutputData(fname2.toStdString()));
    QVERIFY(isTheSame(*dataOnDisk1, *realData1->intensityDataItem()->getOutputData()));
    QVERIFY(isTheSame(*dataOnDisk2, *realData2->intensityDataItem()->getOutputData()));

    // Modifying data and saving the project.
    realData2->intensityDataItem()->setOutputData(createData(value3).release());
    service.save(projectDir);
    QTest::qSleep(10);

    QVERIFY(isTheSame(*dataOnDisk1, *realData1->intensityDataItem()->getOutputData()));
    QVERIFY(isTheSame(*dataOnDisk2, *realData2->intensityDataItem()->getOutputData()) == false);
    // checking that data on disk has changed
    dataOnDisk2.reset(IntensityDataIOFactory::readOutputData(fname2.toStdString()));
    QVERIFY(isTheSame(*dataOnDisk2, *realData2->intensityDataItem()->getOutputData()));

    // Renaming RealData and check that file on disk changed the name
    realData2->setItemName("data2new");
    service.save(projectDir);
    QTest::qSleep(10);

    QString fname2new = "./" + projectDir + "/" + "realdata_data2new_0.int.gz";
    QVERIFY(ProjectUtils::exists(fname2new));
    QVERIFY(isTheSame(fname2new, *realData2->intensityDataItem()->getOutputData()));

    // Check that file with old name was removed.
    QVERIFY(ProjectUtils::exists(fname2) == false);
}

