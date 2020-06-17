#include "ThreadInfo.h"
#include "google_test.h"

class ThreadInfoTest : public ::testing::Test
{
protected:
    ~ThreadInfoTest();

    ThreadInfo thread_info;
};

ThreadInfoTest::~ThreadInfoTest() = default;

TEST_F(ThreadInfoTest, DefaultValues)
{
    EXPECT_EQ(1u, thread_info.n_batches);
    EXPECT_EQ(0u, thread_info.current_batch);
    EXPECT_EQ(0u, thread_info.n_threads);
}
