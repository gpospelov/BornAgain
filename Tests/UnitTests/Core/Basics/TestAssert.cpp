#include "Core/Basics/Assert.h"
#include "Tests/GTestWrapper/google_test.h"

class TestAssert : public ::testing::Test
{
};

TEST_F(TestAssert, Assert)
{
    EXPECT_NO_THROW(ASSERT(1));
#ifdef QT_MESSAGELOGCONTEXT
    EXPECT_EXIT(ASSERT(0), ::testing::KilledBySignal(6), "Assertion failed");
#else
    EXPECT_EXIT(ASSERT(0), ::testing::KilledBySignal(6), "Assertion .* failed");
#endif
}
