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
#include <QGraphicsScene>
#include "gui2/model/materialmodel.h"
#include "gui2/model/sampleitems.h"
#include "gui2/model/samplemodel.h"
#include "gui2/sldeditor/graphicsscene.h"
#include "gui2/sldeditor/layerelementcontroller.h"
#include "gui2/sldeditor/sldelementcontroller.cpp"
#include "gui2/sldeditor/sldelementmodel.h"

using namespace DaRefl;
using namespace ModelView;

class SLDElementControllerTest : public ::testing::Test {
public:
    ~SLDElementControllerTest();

    struct TestData {
        MaterialModel* p_material_model{nullptr};
        SampleModel* p_sample_model{nullptr};
        SLDElementModel* p_sld_model{nullptr};
        GraphicsScene* p_scene_item{nullptr};
        SLDElementController* p_element_controller{nullptr};
        MultiLayerItem* multilayer{nullptr};
        LayerItem* top{nullptr};
        LayerItem* middle{nullptr};
        LayerItem* bottom{nullptr};

        TestData() {
            p_material_model = new MaterialModel();
            p_sample_model = new SampleModel();
            p_sld_model = new SLDElementModel();
            p_scene_item = new GraphicsScene();
            p_element_controller = new SLDElementController(p_material_model, p_sample_model,
                                                            p_sld_model, p_scene_item);

            multilayer = p_sample_model->insertItem<MultiLayerItem>();

            top = p_sample_model->insertItem<LayerItem>(multilayer);
            middle = p_sample_model->insertItem<LayerItem>(multilayer);
            bottom = p_sample_model->insertItem<LayerItem>(multilayer);
        }
    };
};

SLDElementControllerTest::~SLDElementControllerTest() = default;

TEST_F(SLDElementControllerTest, testInit) {
    TestData test_data;

    EXPECT_EQ(1, test_data.p_sample_model->rootItem()->childrenCount());
    EXPECT_EQ(5, test_data.p_sample_model->rootItem()->children().at(0)->childrenCount());
    EXPECT_EQ(3, test_data.p_sld_model->rootItem()->childrenCount());
}

TEST_F(SLDElementControllerTest, testInsertRemoveLayer) {
    TestData test_data;

    auto new_item = test_data.p_sample_model->insertItem<LayerItem>(
        test_data.p_sample_model->rootItem()->children().at(0));

    EXPECT_EQ(1, test_data.p_sample_model->rootItem()->childrenCount());
    EXPECT_EQ(6, test_data.p_sample_model->rootItem()->children().at(0)->childrenCount());
    EXPECT_EQ(4, test_data.p_sld_model->rootItem()->childrenCount());

    test_data.p_sample_model->removeItem(new_item->parent(),
                                         new_item->parent()->tagRowOfItem(new_item));
    EXPECT_EQ(1, test_data.p_sample_model->rootItem()->childrenCount());
    EXPECT_EQ(5, test_data.p_sample_model->rootItem()->children().at(0)->childrenCount());
    EXPECT_EQ(3, test_data.p_sld_model->rootItem()->childrenCount());
}

TEST_F(SLDElementControllerTest, testClearAllLayer) {
    TestData test_data;

    test_data.p_sample_model->removeItem(test_data.top->parent(),
                                         test_data.top->parent()->tagRowOfItem(test_data.top));
    test_data.p_sample_model->removeItem(
        test_data.middle->parent(), test_data.middle->parent()->tagRowOfItem(test_data.middle));
    test_data.p_sample_model->removeItem(
        test_data.bottom->parent(), test_data.bottom->parent()->tagRowOfItem(test_data.bottom));

    EXPECT_EQ(1, test_data.p_sample_model->rootItem()->childrenCount());
    EXPECT_EQ(2, test_data.p_sample_model->rootItem()->children().at(0)->childrenCount());
    EXPECT_EQ(0, test_data.p_sld_model->rootItem()->childrenCount());
}
