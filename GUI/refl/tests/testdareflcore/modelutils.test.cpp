// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include <darefl/model/modelutils.h>
#include <mvvm/standarditems/axisitems.h>
#include <mvvm/standarditems/data1ditem.h>

using namespace ModelView;

//! Tests of Utils namespace functions.

class ModelUtilsTest : public ::testing::Test
{
public:
    ~ModelUtilsTest();
};

ModelUtilsTest::~ModelUtilsTest() = default;

//! Testing CreateDiffVector helper method.

TEST_F(ModelUtilsTest, CreateDiffVector)
{
    std::vector<double> a{1.0, 2.0};
    std::vector<double> b{1.0, 4.0, 3.0};

    auto result = DaRefl::Utils::CreateDiffVector(a, b);
    EXPECT_EQ(result.size(), 2u);
    EXPECT_DOUBLE_EQ(result[0], 0.0);
    EXPECT_DOUBLE_EQ(result[1], 2.0 * (2.0 - 4.0) / (2.0 + 4.0));
}

//! Testing SetDifference helper method.

TEST_F(ModelUtilsTest, SetDifference)
{
    Data1DItem item1;
    item1.setAxis<FixedBinAxisItem>(3, 0.0, 3.0);
    Data1DItem item2;
    item2.setAxis<FixedBinAxisItem>(3, 0.0, 3.0);

    std::vector<double> values1{1.0, 2.0, 3.0};
    std::vector<double> values2{1.0, 4.0, -3.0};
    item1.setValues(values1);
    item2.setValues(values2);

    Data1DItem diff;
    diff.setAxis<FixedBinAxisItem>(3, 0.0, 3.0);
    DaRefl::Utils::SetDifference(&item1, &item2, &diff);

    std::vector<double> expected_centers = {0.5, 1.5, 2.5};
    EXPECT_EQ(diff.binCenters(), expected_centers);
    auto values = diff.binValues();

    EXPECT_EQ(values.size(), 3u);

    auto diff_func = [](auto a, auto b) { return 2.0 * (a - b) / (a + b); };
    EXPECT_FLOAT_EQ(values[0], diff_func(values1[0], values2[0]));
    EXPECT_FLOAT_EQ(values[1], diff_func(values1[1], values2[1]));
    EXPECT_FLOAT_EQ(values[2], 0.0); // division by zero
}
