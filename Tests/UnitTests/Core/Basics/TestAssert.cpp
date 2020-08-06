#include "Core/Basics/Assert.h"
#include "Tests/GTestWrapper/google_test.h"

class TestAssert : public ::testing::Test
{
};

TEST_F(TestAssert, Assert)
{
    EXPECT_NO_THROW(ASSERT(1));
#ifndef _WIN32 // no clue about argument 2 of EXPECT_EXIT under Windows
#ifdef QT_MESSAGELOGCONTEXT
    EXPECT_EXIT(ASSERT(0), ::testing::KilledBySignal(6), "Assertion .* failed .*");
#else
    EXPECT_EXIT(ASSERT(0), ::testing::KilledBySignal(6), "Assertion .* failed");
#endif
#endif
}
