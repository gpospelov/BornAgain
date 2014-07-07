#ifndef MATRIXSPECULARINFOMAPTEST_H
#define MATRIXSPECULARINFOMAPTEST_H

#include "MatrixRTCoefficients.h"
#include "MatrixSpecularInfoMap.h"
#include "gtest/gtest.h"


class MatrixSpecularInfoMapTest : public ::testing :: Test
{
protected:
    MatrixSpecularInfoMapTest();
    virtual ~MatrixSpecularInfoMapTest() {
        delete mp_rtc_default;
    }

    const MatrixRTCoefficients *mp_rtc_default;
    MatrixSpecularInfoMap map;
};

MatrixSpecularInfoMapTest::MatrixSpecularInfoMapTest()
{
    map.addCoefficients(* new MatrixRTCoefficients(), 1.0, 1.0);

    mp_rtc_default = map.getCoefficients(1.0, 1.0);
}

TEST_F(MatrixSpecularInfoMapTest, getCoefficients)
{
    EXPECT_TRUE(NULL != map.getCoefficients(1.0, 1.0));

    EXPECT_EQ(complex_t(0.5,0.0), mp_rtc_default->T1plus()(0));
    EXPECT_EQ(0.0, mp_rtc_default->T1plus()(1));

    EXPECT_EQ(0.0, mp_rtc_default->T1min()(0));
    EXPECT_EQ(complex_t(0.5,0.0), mp_rtc_default->T1min()(1));

    EXPECT_EQ(complex_t(0.5,0.0), mp_rtc_default->T2plus()(0));
    EXPECT_EQ(0.0, mp_rtc_default->T2plus()(1));

    EXPECT_EQ(0.0, mp_rtc_default->T2min()(0));
    EXPECT_EQ(complex_t(0.5,0.0), mp_rtc_default->T2min()(1));

    EXPECT_EQ(complex_t(-0.5,0.0), mp_rtc_default->R1plus()(0));
    EXPECT_EQ(0.0, mp_rtc_default->R1plus()(1));

    EXPECT_EQ(0.0, mp_rtc_default->R1min()(0));
    EXPECT_EQ(complex_t(-0.5,0.0), mp_rtc_default->R1min()(1));

    EXPECT_EQ(complex_t(-0.5,0.0), mp_rtc_default->R2plus()(0));
    EXPECT_EQ(0.0, mp_rtc_default->R2plus()(1));

    EXPECT_EQ(0.0, mp_rtc_default->R2min()(0));
    EXPECT_EQ(complex_t(-0.5,0.0), mp_rtc_default->R2min()(1));

    EXPECT_EQ(complex_t(0.0,0.0), mp_rtc_default->getKz()(0));
    EXPECT_EQ(complex_t(0.0,0.0), mp_rtc_default->getKz()(1));
}



#endif //MATRIXSPECULARINFOMAPTEST_H

