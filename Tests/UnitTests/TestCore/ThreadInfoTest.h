// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      ThreadInfoTest.h
//! @brief     Defines unit test for ThreadInfo class.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef THREADINFOTEST_H_
#define THREADINFOTEST_H_

#include "ThreadInfo.h"

#include "gtest/gtest.h"

class ThreadInfoTest : public ::testing::Test
{
 protected:
    ThreadInfoTest()
        : thread_info() {}

    ThreadInfo thread_info;
};

TEST_F(ThreadInfoTest, DefaultIsSingleBatchAndThread)
{
    EXPECT_EQ(1, thread_info.n_batches);
    EXPECT_EQ(0, thread_info.current_batch);
    EXPECT_EQ(1, thread_info.n_threads);
    EXPECT_EQ(0, thread_info.current_thread);
}

TEST_F(ThreadInfoTest, MakeValuesConsistent)
{
    thread_info.n_batches = 0;
    thread_info.n_threads = -1;
    thread_info.current_batch = -5;
    thread_info.current_thread = 10;
    EXPECT_EQ(0, thread_info.n_batches);
    EXPECT_EQ(-5, thread_info.current_batch);
    EXPECT_EQ(-1, thread_info.n_threads);
    EXPECT_EQ(10, thread_info.current_thread);
    thread_info.imposeConsistency();
    EXPECT_EQ(1, thread_info.n_batches);
    EXPECT_EQ(0, thread_info.current_batch);
    EXPECT_EQ(1, thread_info.n_threads);
    EXPECT_EQ(0, thread_info.current_thread);
}

TEST_F(ThreadInfoTest, BeginIndex)
{
    thread_info.n_batches = 4;
    thread_info.n_threads = 3;

    thread_info.current_batch = 0;
    thread_info.current_thread = 0;
    EXPECT_EQ(0, thread_info.getBeginIndex(20));

    thread_info.current_batch = 0;
    thread_info.current_thread = 1;
    EXPECT_EQ(2, thread_info.getBeginIndex(20));

    thread_info.current_batch = 0;
    thread_info.current_thread = 2;
    EXPECT_EQ(4, thread_info.getBeginIndex(20));

    thread_info.current_batch = 1;
    thread_info.current_thread = 0;
    EXPECT_EQ(5, thread_info.getBeginIndex(20));

    thread_info.current_batch = 2;
    thread_info.current_thread = 0;
    EXPECT_EQ(10, thread_info.getBeginIndex(20));

    thread_info.current_batch = 3;
    thread_info.current_thread = 0;
    EXPECT_EQ(15, thread_info.getBeginIndex(18));

    thread_info.current_batch = 3;
    thread_info.current_thread = 2;
    EXPECT_EQ(17, thread_info.getBeginIndex(18));
}

TEST_F(ThreadInfoTest, EndIndex)
{
    thread_info.n_batches = 4;
    thread_info.n_threads = 3;

    thread_info.current_batch = 0;
    thread_info.current_thread = 0;
    EXPECT_EQ(2, thread_info.getEndIndex(20));

    thread_info.current_batch = 0;
    thread_info.current_thread = 1;
    EXPECT_EQ(4, thread_info.getEndIndex(20));

    thread_info.current_batch = 0;
    thread_info.current_thread = 2;
    EXPECT_EQ(5, thread_info.getEndIndex(20));

    thread_info.current_batch = 1;
    thread_info.current_thread = 0;
    EXPECT_EQ(7, thread_info.getEndIndex(20));

    thread_info.current_batch = 2;
    thread_info.current_thread = 0;
    EXPECT_EQ(12, thread_info.getEndIndex(20));

    thread_info.current_batch = 3;
    thread_info.current_thread = 2;
    EXPECT_EQ(18, thread_info.getEndIndex(18));

    thread_info.current_batch = 3;
    thread_info.current_thread = 2;
    EXPECT_EQ(20, thread_info.getEndIndex(20));
}

TEST_F(ThreadInfoTest, ZeroSizeBatchesThreads)
{
    thread_info.n_batches = 4;
    thread_info.n_threads = 4;

    thread_info.current_batch = 0;
    thread_info.current_thread = 0;
    EXPECT_EQ(0, thread_info.getBeginIndex(10));
    EXPECT_EQ(1, thread_info.getEndIndex(10));

    thread_info.current_batch = 0;
    thread_info.current_thread = 1;
    EXPECT_EQ(1, thread_info.getBeginIndex(10));
    EXPECT_EQ(2, thread_info.getEndIndex(10));

    thread_info.current_batch = 0;
    thread_info.current_thread = 2;
    EXPECT_EQ(2, thread_info.getBeginIndex(10));
    EXPECT_EQ(3, thread_info.getEndIndex(10));

    thread_info.current_batch = 0;
    thread_info.current_thread = 3;
    EXPECT_EQ(10, thread_info.getBeginIndex(10));
    EXPECT_EQ(10, thread_info.getEndIndex(10));

    thread_info.current_batch = 3;
    thread_info.current_thread = 1;
    EXPECT_EQ(10, thread_info.getBeginIndex(10));
    EXPECT_EQ(10, thread_info.getEndIndex(10));

    thread_info.current_batch = 3;
    thread_info.current_thread = 2;
    EXPECT_EQ(10, thread_info.getBeginIndex(10));
    EXPECT_EQ(10, thread_info.getEndIndex(10));
}



#endif /* THREADINFOTEST_H_ */
