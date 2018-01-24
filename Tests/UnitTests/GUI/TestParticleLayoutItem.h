#include "InterferenceFunctionItems.h"
#include "ParticleLayoutItem.h"
#include "SampleModel.h"
#include "SessionItemUtils.h"
#include "google_test.h"

class TestParticleLayoutItem : public ::testing::Test
{
public:
    ~TestParticleLayoutItem();
};

TestParticleLayoutItem::~TestParticleLayoutItem() = default;

using namespace SessionItemUtils;

//! Checks enabled/disabled status of TotalDensity when adding interference function items.

TEST_F(TestParticleLayoutItem, densityAppearance)
{
    SampleModel model;
    auto layout
        = dynamic_cast<ParticleLayoutItem*>(model.insertNewItem(Constants::ParticleLayoutType));

    // empty layout should have TotalDensity enabled
    EXPECT_TRUE(layout->getItem(ParticleLayoutItem::P_TOTAL_DENSITY)->isEnabled());

    // adding radial paracrystal shouldn't change it
    auto interference
        = model.insertNewItem(Constants::InterferenceFunctionRadialParaCrystalType,
                              model.indexOfItem(layout), -1, ParticleLayoutItem::T_INTERFERENCE);
    EXPECT_TRUE(layout->getItem(ParticleLayoutItem::P_TOTAL_DENSITY)->isEnabled());

    // removing paracrystal, TotalDensity still enabled
    layout->takeRow(ParentRow(*interference));
    EXPECT_TRUE(layout->getItem(ParticleLayoutItem::P_TOTAL_DENSITY)->isEnabled());
    delete interference;

    // adding 2d interference, TotalDensity should be disabled
    interference
        = model.insertNewItem(Constants::InterferenceFunction2DLatticeType,
                              model.indexOfItem(layout), -1, ParticleLayoutItem::T_INTERFERENCE);
    EXPECT_FALSE(layout->getItem(ParticleLayoutItem::P_TOTAL_DENSITY)->isEnabled());

    // removing 2D interference, TotalIntensity should be reenabled
    layout->takeRow(ParentRow(*interference));
    EXPECT_TRUE(layout->getItem(ParticleLayoutItem::P_TOTAL_DENSITY)->isEnabled());
    delete interference;
}
