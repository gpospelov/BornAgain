#include "AxesItems.h"
#include "FixedBinAxis.h"
#include "GUIHelpers.h"
#include "PropertyItem.h"
#include "TransformFromDomain.h"
#include "Units.h"
#include "VariableBinAxis.h"
#include "google_test.h"

class TestAxesItems : public ::testing::Test
{
};

TEST_F(TestAxesItems, transformFromDomain)
{
    BasicAxisItem item;

    // transform domain axis without scale factor
    FixedBinAxis axis0("axis0", 99, -42.0, 42.0);
    TransformFromDomain::setAxisItem(&item, axis0);
    EXPECT_EQ(item.getItemValue(BasicAxisItem::P_NBINS), static_cast<int>(axis0.size()));
    EXPECT_EQ(item.getItemValue(BasicAxisItem::P_MIN), static_cast<int>(axis0.getMin()));
    EXPECT_EQ(item.getItemValue(BasicAxisItem::P_MAX), static_cast<int>(axis0.getMax()));
    EXPECT_EQ(item.getItemValue(BasicAxisItem::P_TITLE), QString::fromStdString(axis0.getName()));

    // transform domain axis with limits given in radians
    FixedBinAxis axis1("axis1", 42, -42.0 * Units::deg, 42.0 * Units::deg);
    const double scale = 1. / Units::deg;
    TransformFromDomain::setAxisItem(&item, axis1, scale);
    EXPECT_EQ(item.getItemValue(BasicAxisItem::P_NBINS), static_cast<int>(axis1.size()));
    EXPECT_EQ(item.getItemValue(BasicAxisItem::P_MIN), -42.0);
    EXPECT_EQ(item.getItemValue(BasicAxisItem::P_MAX), 42.0);
    EXPECT_EQ(item.getItemValue(BasicAxisItem::P_TITLE), QString::fromStdString(axis1.getName()));

    // transform to unexpected item
    PropertyItem property;
    EXPECT_THROW(TransformFromDomain::setAxisItem(&property, axis1), GUIHelpers::Error);

    // transform from unexpected axis
    std::vector<double> bins = {1.0, 2.0, 3.0};
    VariableBinAxis varaxis("axis", bins.size() - 1, bins);
    EXPECT_THROW(TransformFromDomain::setAxisItem(&item, varaxis), GUIHelpers::Error);
}
