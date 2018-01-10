#include "google_test.h"
#include "ThreadInfo.h"

class ThreadInfoTest : public ::testing::Test
{
protected:
    ~ThreadInfoTest();

    ThreadInfo thread_info;
};

ThreadInfoTest::~ThreadInfoTest() = default;

TEST_F(ThreadInfoTest, DefaultValues)
{
    EXPECT_EQ(1, thread_info.n_batches);
    EXPECT_EQ(0, thread_info.current_batch);
    EXPECT_EQ(0, thread_info.n_threads);
}
