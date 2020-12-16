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
#include "gui2/importdataview/dataselectionmodel.h"
#include "gui2/importdataview/dataviewmodel.h"
#include "gui2/importdataview/graphimportdata.h"
#include "gui2/importdataview/importdataeditoractions.h"
#include "gui2/model/experimentaldataitems.h"
#include "gui2/model/experimentaldatamodel.h"
#include "mvvm/model/comboproperty.h"
#include "mvvm/model/modelutils.h"
#include "mvvm/standarditems/graphitem.h"
#include "mvvm/standarditems/plottableitems.h"

using namespace DaRefl;
using namespace ModelView;

//! Tests of ImportDataEditorActions.

class ImportDataEditorActionsTest : public ::testing::Test {
public:
    ~ImportDataEditorActionsTest();

    struct TestData {
        ExperimentalDataModel data_model;
        DataViewModel view_model{&data_model};
        DataSelectionModel selection_model{&view_model};
        CanvasItem* canvas0{nullptr};
        ModelView::GraphItem* graph0{nullptr};
        ModelView::GraphItem* graph1{nullptr};
        ImportDataEditorActions actions{&data_model};
        TestData() {
            canvas0 = data_model.addCanvas();

            GraphImportData raw_data = {"", {42}, "", {42}, ""};
            graph0 = data_model.addGraph(raw_data, *canvas0);
            graph1 = data_model.addGraph(raw_data, *canvas0);

            view_model.setRootSessionItem(data_model.canvasContainer());
            actions.setSelectionModel(&selection_model);
        }
    };
};

ImportDataEditorActionsTest::~ImportDataEditorActionsTest() = default;

//! Checks onAddCanvas.

TEST_F(ImportDataEditorActionsTest, onAddCanvas) {
    ExperimentalDataModel model;
    ImportDataEditorActions actions(&model);

    EXPECT_EQ(model.canvasContainer()->canvasItems().size(), 0);
    actions.onAddCanvas();
    EXPECT_EQ(model.canvasContainer()->canvasItems().size(), 1);
}

//! Checks onAddCanvas.

TEST_F(ImportDataEditorActionsTest, onDeleteItem) {
    TestData test_data;
    EXPECT_EQ(test_data.data_model.canvasContainer()->canvasItems().size(), 1);
    EXPECT_EQ(test_data.data_model.dataContainer()->dataItems().size(), 2);

    test_data.selection_model.selectItem(test_data.canvas0);

    test_data.actions.onDeleteItem();

    EXPECT_EQ(test_data.data_model.canvasContainer()->canvasItems().size(), 0);
    EXPECT_EQ(test_data.data_model.dataContainer()->dataItems().size(), 0);
}

//! Checks line style change on selection changed.

TEST_F(ImportDataEditorActionsTest, onSelectionChanged) {
    TestData test_data;

    test_data.selection_model.selectItem(test_data.graph0);

    auto pen0 = test_data.graph0->penItem();
    auto pen1 = test_data.graph1->penItem();

    auto pencombo0 = pen0->property<ModelView::ComboProperty>(ModelView::PenItem::P_STYLE);
    auto pencombo1 = pen1->property<ModelView::ComboProperty>(ModelView::PenItem::P_STYLE);
    EXPECT_EQ(pencombo0.currentIndex(), 2); // correspond to dashed line (i.e. selected)
    EXPECT_EQ(pencombo1.currentIndex(), 1); // correspond to solid line

    test_data.selection_model.selectItem(test_data.graph1);
    pencombo0 = pen0->property<ModelView::ComboProperty>(ModelView::PenItem::P_STYLE);
    pencombo1 = pen1->property<ModelView::ComboProperty>(ModelView::PenItem::P_STYLE);
    EXPECT_EQ(pencombo0.currentIndex(), 1); // correspond to solid line
    EXPECT_EQ(pencombo1.currentIndex(), 2); // correspond to dashed line (i.e. selected)
}
