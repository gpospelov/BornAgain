// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include <darefl/model/experimentaldataitems.h>
#include <darefl/model/instrumentitems.h>
#include <darefl/model/instrumentmodel.h>
#include "mvvm/model/sessionmodel.h"
#include "mvvm/standarditems/axisitems.h"
#include "mvvm/standarditems/data1ditem.h"
#include "mvvm/standarditems/graphitem.h"

using namespace DaRefl;
using namespace ModelView;

//! Tests of ExperimentalDataModel.

class InstrumentItemsTest : public ::testing::Test {
public:
    ~InstrumentItemsTest();
};

InstrumentItemsTest::~InstrumentItemsTest() = default;

TEST_F(InstrumentItemsTest, experimentalScanItemInitialState) {
    ExperimentalScanItem item;
    EXPECT_EQ(item.graphItem(), nullptr);
    EXPECT_TRUE(item.qScanValues().empty());
}

TEST_F(InstrumentItemsTest, experimentalScanGetValues) {
    InstrumentModel model;

    // preparing DataItem
    auto data_item = model.insertItem<Data1DItem>();
    std::vector<double> expected_content = {1.0, 2.0, 3.0};
    std::vector<double> expected_centers = {0.5, 1.5, 2.5};
    data_item->setAxis<FixedBinAxisItem>(3, 0.0, 3.0);
    data_item->setValues(expected_content);

    // preparing GraphItem
    auto graph_item = model.insertItem<GraphItem>();
    graph_item->setDataItem(data_item);

    // preparing ScanItem
    auto scan_item = model.insertItem<ExperimentalScanItem>();
    scan_item->setGraphItem(graph_item);

    EXPECT_EQ(scan_item->graphItem(), graph_item);
    EXPECT_EQ(scan_item->qScanValues(), expected_centers);
}
