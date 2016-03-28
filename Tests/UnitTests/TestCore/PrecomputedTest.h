#ifndef PRECOMPUTEDTEST_H
#define PRECOMPUTEDTEST_H

#include "Precomputed.h"
#include "gtest/gtest.h"
#include <memory>

class PrecomputedTest : public ::testing::Test
{
public:
};

TEST_F(PrecomputedTest, Factorial)
{
    const double eps = 2.3e-16; // about the machine precision
    auto& precomputed = IPrecomputed::instance();
    EXPECT_TRUE(precomputed.factorial.size()>150); 
    EXPECT_DOUBLE_EQ(precomputed.factorial[0], 1.);
    EXPECT_DOUBLE_EQ(precomputed.factorial[1], 1.);
    EXPECT_DOUBLE_EQ(precomputed.factorial[2], 2.);
    EXPECT_DOUBLE_EQ(precomputed.factorial[3], 6.);
    for( size_t k=4; k<precomputed.factorial.size(); ++k )
        EXPECT_NEAR(precomputed.factorial[k], tgamma(k+1.), 4*eps*tgamma(k+1.) );
}

#endif
