#include "LayerFillLimits.h"
#include <stdexcept>

class LayerFillLimitsTest : public ::testing::Test
{
protected:
    LayerFillLimitsTest();
    virtual ~LayerFillLimitsTest();
};

LayerFillLimitsTest::LayerFillLimitsTest()
{}

LayerFillLimitsTest::~LayerFillLimitsTest()
{}

TEST_F(LayerFillLimitsTest, LayerFillLimitsEmptyConstructor)
{
    LayerFillLimits layer_limits( {} );
    EXPECT_TRUE(layer_limits.layerZLimits().size()==1);
    EXPECT_TRUE(layer_limits.layerZLimits()[0]==ZLimits());
}

