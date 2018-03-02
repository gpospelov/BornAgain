#include "google_test.h"
#include "Numeric.h"
#include <algorithm>

class RelDiffTest : public ::testing::Test
{
protected:
    ~RelDiffTest();
};

RelDiffTest::~RelDiffTest() = default;

TEST_F(RelDiffTest, RelDiffAlmostEq)
{
    EXPECT_TRUE(Numeric::areAlmostEqual(+1e+120, +1e+120, 1.));
    EXPECT_TRUE(Numeric::areAlmostEqual(+1e-120, +1e-120, 1.));
    EXPECT_TRUE(Numeric::areAlmostEqual(0, 0, 1.));
    EXPECT_TRUE(Numeric::areAlmostEqual(-1e-120, -1e-120, 1.));
    EXPECT_TRUE(Numeric::areAlmostEqual(-1e+120, -1e+120, 1.));

    EXPECT_FALSE(Numeric::areAlmostEqual(+1e+120, 0, 1.));
    EXPECT_FALSE(Numeric::areAlmostEqual(-1e+120, 0, 1.));
}
