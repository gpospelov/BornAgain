#include "GUI/coregui/Models/ComboProperty.h"
#include "GUI/coregui/Models/DocumentModel.h"
#include "GUI/coregui/Models/LayerItem.h"
#include "GUI/coregui/Models/MultiLayerItem.h"
#include "GUI/coregui/Models/ParticleCompositionItem.h"
#include "GUI/coregui/Models/ParticleDistributionItem.h"
#include "GUI/coregui/Models/ParticleItem.h"
#include "GUI/coregui/Models/ParticleLayoutItem.h"
#include "GUI/coregui/Models/SampleModel.h"
#include "GUI/coregui/Models/SessionItemUtils.h"
#include "GUI/coregui/Models/SimulationOptionsItem.h"
#include "Tests/GTestWrapper/google_test.h"
#include <QtTest>

using SessionItemUtils::ParentRow;

class TestMapperCases : public ::testing::Test {
};

TEST_F(TestMapperCases, test_ParticeleCompositionUpdate)
{
    SampleModel model;
    auto multilayer = model.insertItem<MultiLayerItem>();
    auto layer = model.insertItem<LayerItem>(multilayer);
    auto layout = model.insertItem<ParticleLayoutItem>(layer);

    // composition added to layout should have abundance enabled
    auto compositionFree = model.insertItem<ParticleCompositionItem>(layout);
    EXPECT_TRUE(compositionFree->getItem(ParticleItem::P_ABUNDANCE)->isEnabled());

    // composition added to distribution should have abundance disabled
    auto distribution = model.insertItem<ParticleDistributionItem>(layout);
    auto composition = model.insertItem<ParticleCompositionItem>(distribution);
    EXPECT_FALSE(composition->getItem(ParticleItem::P_ABUNDANCE)->isEnabled());

    auto taken = distribution->takeRow(ParentRow(*composition));
    EXPECT_TRUE(taken->getItem(ParticleItem::P_ABUNDANCE)->isEnabled());
    delete taken;
}

TEST_F(TestMapperCases, test_SimulationOptionsComputationToggle)
{
    DocumentModel model;
    model.insertItem<SimulationOptionsItem>();

    SimulationOptionsItem* item = model.simulationOptionsItem();

    ComboProperty combo =
        item->getItemValue(SimulationOptionsItem::P_COMPUTATION_METHOD).value<ComboProperty>();
    EXPECT_EQ(combo.getValue(), "Analytical");
    EXPECT_FALSE(item->getItem(SimulationOptionsItem::P_MC_POINTS)->isEnabled());

    combo.setValue("Monte-Carlo Integration");
    item->setItemValue(SimulationOptionsItem::P_COMPUTATION_METHOD, combo.variant());
    EXPECT_TRUE(item->getItem(SimulationOptionsItem::P_MC_POINTS)->isEnabled());
}
