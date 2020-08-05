#include "Core/Basics/Assert.h"
#include "Tests/GTestWrapper/google_test.h"

class TestAssert : public ::testing::Test
{
};

TEST_F(TestAssert, Assert)
{
    EXPECT_NO_THROW(ASSERT(1));
    EXPECT_EXIT(ASSERT(0), ::testing::ExitedWithCode(1), "assertion failed");
}
