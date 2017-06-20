#include <QtTest>
#include "ApplicationModels.h"
#include "OutputDataIOService.h"
#include "RealDataItem.h"
#include "JobModel.h"
#include "JobItem.h"
#include "JobItemUtils.h"
#include "IntensityDataItem.h"
#include <QSignalSpy>
#include <QDebug>

class TestOutputDataIOService : public QObject
{
    Q_OBJECT

private slots:
    void test_nonXMLData();
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
    // It returns only IntensityDataItem which have non-zero intensities
    OutputDataIOService service(&models);
    QCOMPARE(service.dataItems().size(), 3);
}

