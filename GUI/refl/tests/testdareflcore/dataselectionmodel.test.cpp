// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include "test_utils.h"
#include <QDebug>
#include <darefl/importdataview/dataselectionmodel.h>
#include <darefl/importdataview/dataviewmodel.h>
#include <darefl/model/experimentaldataitems.h>
#include <darefl/model/experimentaldatamodel.h>
#include "mvvm/model/modelutils.h"
#include "mvvm/standarditems/graphitem.h"

using namespace DaRefl;
using namespace ModelView;

//! Tests of DataSelectionModel.

class DataSelectionModelTest : public ::testing::Test {
public:
    ~DataSelectionModelTest();

    struct TestData {
        ExperimentalDataModel data_model;
        DataViewModel view_model{&data_model};
        DataSelectionModel selection_model{&view_model};
        CanvasContainerItem* container{nullptr};
        CanvasItem* canvas0{nullptr};
        GraphItem* graph_c0_a{nullptr};
        GraphItem* graph_c0_b{nullptr};
        CanvasItem* canvas1{nullptr};
        GraphItem* graph_c1_a{nullptr};
        TestData() {
            container = Utils::TopItem<CanvasContainerItem>(&data_model);
            canvas0 = data_model.insertItem<CanvasItem>(container);
            graph_c0_a = data_model.insertItem<GraphItem>(canvas0);
            graph_c0_b = data_model.insertItem<GraphItem>(canvas0);
            canvas1 = data_model.insertItem<CanvasItem>(container);
            graph_c1_a = data_model.insertItem<GraphItem>(canvas1);
            view_model.setRootSessionItem(container);
        }
    };
};

DataSelectionModelTest::~DataSelectionModelTest() = default;

//! Initial state of selection model.

TEST_F(DataSelectionModelTest, initialState) {
    TestData test_data;
    // checking layout of container with test data
    EXPECT_EQ(test_data.container->size(), 2);

    // checking that no selection exists
    EXPECT_FALSE(test_data.selection_model.hasSelection());
    EXPECT_EQ(test_data.selection_model.activeCanvas(), nullptr);
    EXPECT_EQ(test_data.selection_model.selectedGraph(), nullptr);
    EXPECT_EQ(test_data.selection_model.selectedCanvas().size(), 0);
    EXPECT_EQ(test_data.selection_model.selectedGraphs().size(), 0);
}

//! Select single canvas and check that it was actually selected.

TEST_F(DataSelectionModelTest, selectCanvasItem) {
    TestData test_data;
    EXPECT_FALSE(test_data.selection_model.hasSelection());

    // make canvas0 selected
    test_data.selection_model.selectItem(test_data.canvas0);

    EXPECT_TRUE(test_data.selection_model.hasSelection());
    EXPECT_EQ(test_data.selection_model.selectedIndexes().size(), 2); // CanvasItem, ViewEmptyItem

    std::vector<SessionItem*> expected = {test_data.canvas0};
    EXPECT_EQ(test_data.selection_model.selectedItems(), expected);

    // check that selection model reports same canvas as active one
    EXPECT_EQ(test_data.selection_model.activeCanvas(), test_data.canvas0);
    std::vector<CanvasItem*> expected_canvas{test_data.canvas0};
    EXPECT_EQ(test_data.selection_model.selectedCanvas(), expected_canvas);

    // no graphs selected
    EXPECT_EQ(test_data.selection_model.selectedGraph(), nullptr);
    EXPECT_EQ(test_data.selection_model.selectedGraphs().size(), 0);
}

//! Select single graph and check reported selection.

TEST_F(DataSelectionModelTest, selectGraph) {
    TestData test_data;
    EXPECT_FALSE(test_data.selection_model.hasSelection());

    // make graph0 selected
    test_data.selection_model.selectItem(test_data.graph_c0_a);

    EXPECT_TRUE(test_data.selection_model.hasSelection());
    EXPECT_EQ(test_data.selection_model.selectedIndexes().size(), 2); // GraphItem, LabelItem

    std::vector<SessionItem*> expected = {test_data.graph_c0_a};
    EXPECT_EQ(test_data.selection_model.selectedItems(), expected);

    // method should report parent of graph as active canvas
    EXPECT_EQ(test_data.selection_model.activeCanvas(), test_data.canvas0);

    // no canvas selected
    EXPECT_EQ(test_data.selection_model.selectedCanvas(), std::vector<CanvasItem*>());

    // method should report parent of graph as selected canvas
    EXPECT_EQ(test_data.selection_model.selectedGraph(), test_data.graph_c0_a);
    std::vector<ModelView::GraphItem*> expected_graphs{test_data.graph_c0_a};
    EXPECT_EQ(test_data.selection_model.selectedGraphs(), expected_graphs);
}

//! Select two graphs and check reported selection.

TEST_F(DataSelectionModelTest, selectTwoGraphs) {
    TestData test_data;
    EXPECT_FALSE(test_data.selection_model.hasSelection());

    // make two graphs selected
    std::vector<SessionItem*> expected = {test_data.graph_c0_a, test_data.graph_c0_b};
    test_data.selection_model.selectItems(expected);

    EXPECT_TRUE(test_data.selection_model.hasSelection());
    EXPECT_EQ(test_data.selection_model.selectedIndexes().size(), 4); // GraphItem, LabelItem

    EXPECT_EQ(test_data.selection_model.selectedItems(), expected);

    // method should report parent of graph as active canvas
    EXPECT_EQ(test_data.selection_model.activeCanvas(), test_data.canvas0);
    EXPECT_EQ(test_data.selection_model.selectedCanvas().size(), 0);

    // method should report parent of graph as selected canvas
    EXPECT_EQ(test_data.selection_model.selectedGraph(), test_data.graph_c0_a);
    std::vector<ModelView::GraphItem*> expected_graphs{test_data.graph_c0_a, test_data.graph_c0_b};
    EXPECT_EQ(test_data.selection_model.selectedGraphs(), expected_graphs);
}

//! Select two graphs and check reported selection.

// FIXME Enable test. For that DataSelectionModel should allow to select
// parent+child programmatically.

// TEST_F(DataSelectionModelTest, selectGraphAndCanvas)
//{
//    TestData test_data;
//    EXPECT_FALSE(test_data.selection_model.hasSelection());

//    // make two graphs selected
//    std::vector<SessionItem*> expected = {test_data.graph_c0_a, test_data.canvas0};
//    test_data.selection_model.selectItems(expected);

//    EXPECT_TRUE(test_data.selection_model.hasSelection());
//    EXPECT_EQ(test_data.selection_model.selectedIndexes().size(), 4); // GraphItem, LabelItem
//}
