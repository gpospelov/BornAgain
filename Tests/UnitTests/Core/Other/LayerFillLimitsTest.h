#include "LayerFillLimits.h"
#include <stdexcept>

class LayerFillLimitsTest : public ::testing::Test
{
protected:
    LayerFillLimitsTest();
    virtual ~LayerFillLimitsTest();

    LayerFillLimits m_fill_limits;
    std::vector<double> layers_bottomz;
};

LayerFillLimitsTest::LayerFillLimitsTest()
    : m_fill_limits( {} )
{
    std::vector<double> layers_bottomz = { 0, -5, -20 };
    m_fill_limits = LayerFillLimits(layers_bottomz);
}

LayerFillLimitsTest::~LayerFillLimitsTest()
{}

TEST_F(LayerFillLimitsTest, LayerFillLimitsEmptyConstructor)
{
    LayerFillLimits layer_limits( {} );
    EXPECT_TRUE(layer_limits.layerZLimits().size()==1);
    EXPECT_TRUE(layer_limits.layerZLimits()[0]==ZLimits());
}

TEST_F(LayerFillLimitsTest, LayerFillLimitsConstructor)
{
    std::vector<ZLimits> limits = m_fill_limits.layerZLimits();
    EXPECT_EQ(4u, limits.size());
    EXPECT_TRUE(limits[0]==ZLimits());
    EXPECT_TRUE(limits[1]==ZLimits());
    EXPECT_TRUE(limits[2]==ZLimits());
    EXPECT_TRUE(limits[3]==ZLimits());
}

TEST_F(LayerFillLimitsTest, LayerFillLimitsWrongUpdate)
{
    EXPECT_THROW(m_fill_limits.update( { 1, 0 }), std::runtime_error);
    std::vector<ZLimits> limits = m_fill_limits.layerZLimits();
    EXPECT_EQ(4u, limits.size());
    EXPECT_TRUE(limits[0]==ZLimits());
    EXPECT_TRUE(limits[1]==ZLimits());
    EXPECT_TRUE(limits[2]==ZLimits());
    EXPECT_TRUE(limits[3]==ZLimits());
}

TEST_F(LayerFillLimitsTest, LayerFillLimitsUpdate)
{
    m_fill_limits.update( { 1, 1.5 });
    std::vector<ZLimits> limits = m_fill_limits.layerZLimits();
    EXPECT_EQ(4u, limits.size());
    EXPECT_TRUE(limits[0]==ZLimits(0, 1.5));
    EXPECT_TRUE(limits[1]==ZLimits());
    EXPECT_TRUE(limits[2]==ZLimits());
    EXPECT_TRUE(limits[3]==ZLimits());

    m_fill_limits.update( { -6, -3 });
    limits = m_fill_limits.layerZLimits();
    EXPECT_EQ(4u, limits.size());
    EXPECT_TRUE(limits[0]==ZLimits(0, 1.5));
    EXPECT_TRUE(limits[1]==ZLimits(-5, -3));
    EXPECT_TRUE(limits[2]==ZLimits(-1, 0));
    EXPECT_TRUE(limits[3]==ZLimits());

    m_fill_limits.update( { -10, -7 });
    limits = m_fill_limits.layerZLimits();
    EXPECT_EQ(4u, limits.size());
    EXPECT_TRUE(limits[0]==ZLimits(0, 1.5));
    EXPECT_TRUE(limits[1]==ZLimits(-5, -3));
    EXPECT_TRUE(limits[2]==ZLimits(-5, 0));
    EXPECT_TRUE(limits[3]==ZLimits());

    m_fill_limits.update( { -30, -25 });
    limits = m_fill_limits.layerZLimits();
    EXPECT_EQ(4u, limits.size());
    EXPECT_TRUE(limits[0]==ZLimits(0, 1.5));
    EXPECT_TRUE(limits[1]==ZLimits(-5, -3));
    EXPECT_TRUE(limits[2]==ZLimits(-5, 0));
    EXPECT_TRUE(limits[3]==ZLimits(-10, 0));
}

