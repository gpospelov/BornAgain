#include "GUI/coregui/Models/ComboProperty.h"
#include "GUI/coregui/Models/DocumentModel.h"
#include "GUI/coregui/Models/ParticleItem.h"
#include "GUI/coregui/Models/ParticleLayoutItem.h"
#include "GUI/coregui/Models/SampleModel.h"
#include "GUI/coregui/Models/SessionItemUtils.h"
#include "GUI/coregui/Models/SimulationOptionsItem.h"
#include "Tests/UnitTests/utilities/google_test.h"
#include <QtTest>

using SessionItemUtils::ParentRow;

class TestMapperCases : public ::testing::Test
{
};

TEST_F(TestMapperCases, test_ParticeleCompositionUpdate)
{
    SampleModel model;
    SessionItem* multilayer = model.insertNewItem(Constants::MultiLayerType);
    SessionItem* layer = model.insertNewItem(Constants::LayerType, multilayer->index());
    SessionItem* layout = model.insertNewItem(Constants::ParticleLayoutType, layer->index());

    // composition added to layout should have abundance enabled
    SessionItem* compositionFree =
        model.insertNewItem(Constants::ParticleCompositionType, layout->index());
    EXPECT_TRUE(compositionFree->getItem(ParticleItem::P_ABUNDANCE)->isEnabled());

    // composition added to distribution should have abundance disabled
    SessionItem* distribution =
        model.insertNewItem(Constants::ParticleDistributionType, layout->index());
    SessionItem* composition =
        model.insertNewItem(Constants::ParticleCompositionType, distribution->index());
    EXPECT_TRUE(composition->getItem(ParticleItem::P_ABUNDANCE)->isEnabled() == false);

    composition = distribution->takeRow(ParentRow(*composition));
    EXPECT_TRUE(composition->getItem(ParticleItem::P_ABUNDANCE)->isEnabled());
    delete composition;
}

TEST_F(TestMapperCases, test_SimulationOptionsComputationToggle)
{
    DocumentModel model;
    model.insertNewItem(Constants::SimulationOptionsType);

    SimulationOptionsItem* item = model.simulationOptionsItem();

    ComboProperty combo =
        item->getItemValue(SimulationOptionsItem::P_COMPUTATION_METHOD).value<ComboProperty>();
    EXPECT_EQ(combo.getValue(), Constants::SIMULATION_ANALYTICAL);
    EXPECT_TRUE(item->getItem(SimulationOptionsItem::P_MC_POINTS)->isEnabled() == false);

    combo.setValue(Constants::SIMULATION_MONTECARLO);
    item->setItemValue(SimulationOptionsItem::P_COMPUTATION_METHOD, combo.variant());
    EXPECT_TRUE(item->getItem(SimulationOptionsItem::P_MC_POINTS)->isEnabled() == true);
}
