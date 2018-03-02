#include "google_test.h"
#include "FormFactors.h"
#include "FormFactorItems.h"
#include "Units.h"
#include "Numeric.h"

class TestFormFactorItems :  public ::testing::Test
{
public:
    ~TestFormFactorItems();
};

TestFormFactorItems::~TestFormFactorItems() = default;

TEST_F(TestFormFactorItems, test_AnisoPyramidItem)
{
    // to domain
    AnisoPyramidItem item;
    item.setItemValue(AnisoPyramidItem::P_LENGTH, 20.0);
    item.setItemValue(AnisoPyramidItem::P_WIDTH, 16.0);
    item.setItemValue(AnisoPyramidItem::P_HEIGHT, 13.0);
    item.setItemValue(AnisoPyramidItem::P_ALPHA, 60.0);
    auto P_ff = item.createFormFactor();
    FormFactorAnisoPyramid* p_ff = dynamic_cast<FormFactorAnisoPyramid*>(P_ff.get());
    EXPECT_TRUE(p_ff);
    EXPECT_EQ(p_ff->getLength(), 20.0);
    EXPECT_EQ(p_ff->getWidth(), 16.0);
    EXPECT_EQ(p_ff->getHeight(), 13.0);
    EXPECT_TRUE(Numeric::areAlmostEqual(p_ff->getAlpha(), Units::deg2rad(60.0)));
}
