#ifndef SCALARSPECULARINFOMAPTEST_H
#define SCALARSPECULARINFOMAPTEST_H

#include "ScalarRTCoefficients.h"
#include "ScalarSpecularInfoMap.h"
#include "gtest/gtest.h"


class ScalarSpecularInfoMapTest : public ::testing :: Test
{
protected:
    ScalarSpecularInfoMapTest();
    virtual ~ScalarSpecularInfoMapTest(){}

//    ScalarSpecularInfoMap map;
    ScalarRTCoefficients *mp_rt_custom;

};


ScalarSpecularInfoMapTest::ScalarSpecularInfoMapTest()
{
    ScalarRTCoefficients srtc;
    srtc.lambda = complex_t(1.0, 1.0);
    srtc.kz = complex_t(1.0, 1.0);
    srtc.t_r(0) = complex_t(0.0, 0.5);
    srtc.t_r(1) = complex_t(1.0, 0.5);
//    map.addCoefficients(srtc, 1.0, 1.0);


//    mp_rt_custom = map.getCoefficients(1.0, 1.0);
}

TEST_F(ScalarSpecularInfoMapTest, getCoefficients)
{
//    EXPECT_TRUE(NULL != map.getCoefficients(1.0, 1.0));

//    EXPECT_EQ(complex_t(0.0,0.0), mp_rt_custom.T1plus()(0));
//    EXPECT_EQ(0.0, mp_rt_custom.T1plus()(1));

//    EXPECT_EQ(0.0, mp_rt_custom.T1min()(0));
//    EXPECT_EQ(complex_t(0.0,0.5), mp_rt_custom.T1min()(1));

//    EXPECT_EQ(complex_t(0.0, 0.5), mp_rt_custom.T2plus()(0));
//    EXPECT_EQ(0.0, mp_rt_custom.T2plus()(1));

//    EXPECT_EQ(0.0, mp_rt_custom.T2min()(0));
//    EXPECT_EQ(complex_t(0.0,0.0), mp_rt_custom.T2min()(1));

//    EXPECT_EQ(complex_t(0.0,0.0), mp_rt_custom.R1plus()(0));
//    EXPECT_EQ(0.0, mp_rt_custom.R1plus()(1));

//    EXPECT_EQ(0.0, mp_rt_custom.R1min()(0));
//    EXPECT_EQ(complex_t(1.0,0.5), mp_rt_custom.R1min()(1));

//    EXPECT_EQ(complex_t(1.0,0.5), mp_rt_custom.R2plus()(0));
//    EXPECT_EQ(0.0, mp_rt_custom.R2plus()(1));

//    EXPECT_EQ(0.0, mp_rt_custom.R2min()(0));
//    EXPECT_EQ(complex_t(0.0,0.0), mp_rt_custom.R2min()(1));

//    EXPECT_EQ(complex_t(1.0,1.0), mp_rt_custom.getKz()(0));
//    EXPECT_EQ(complex_t(1.0,1.0), mp_rt_custom.getKz()(1));

//    EXPECT_EQ(complex_t(0.0,0.5), mp_rt_custom.getScalarT());
//    EXPECT_EQ(complex_t(1.0,0.5), mp_rt_custom.getScalarR());
//    EXPECT_EQ(complex_t(1.0,1.0), mp_rt_custom.getScalarKz());
}



#endif //SCALARSPECULARINFOMAPTEST_H
