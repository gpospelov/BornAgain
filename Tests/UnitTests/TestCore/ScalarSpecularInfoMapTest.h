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

    ScalarSpecularInfoMap map;
    ScalarRTCoefficients scrtCustom;

};


ScalarSpecularInfoMapTest::ScalarSpecularInfoMapTest()
{
    ScalarRTCoefficients srtc;
    srtc.lambda = complex_t(1.0, 1.0);
    srtc.kz = complex_t(1.0, 1.0);
    srtc.phi_psi(0) = complex_t(1.0, 1.0);
    srtc.phi_psi(1) = complex_t(1.0, 1.0);
    map.addCoefficients(srtc, 1.0, 1.0);


    scrtCustom = *map.getCoefficients(1.0, 1.0);
}

TEST_F(ScalarSpecularInfoMapTest, getCoefficients)
{
    EXPECT_TRUE(NULL != map.getCoefficients(1.0, 1.0));

    EXPECT_EQ(complex_t(0.0,0.0), scrtCustom.T1plus()(0));
    EXPECT_EQ(0.0, scrtCustom.T1plus()(1));

    EXPECT_EQ(0.0, scrtCustom.T1min()(0));
    EXPECT_EQ(complex_t(0.0,0.5), scrtCustom.T1min()(1));

    EXPECT_EQ(complex_t(0.0, 0.5), scrtCustom.T2plus()(0));
    EXPECT_EQ(0.0, scrtCustom.T2plus()(1));

    EXPECT_EQ(0.0, scrtCustom.T2min()(0));
    EXPECT_EQ(complex_t(0.0,0.0), scrtCustom.T2min()(1));

    EXPECT_EQ(complex_t(0.0,0.0), scrtCustom.R1plus()(0));
    EXPECT_EQ(0.0, scrtCustom.R1plus()(1));

    EXPECT_EQ(0.0, scrtCustom.R1min()(0));
    EXPECT_EQ(complex_t(1.0,0.5), scrtCustom.R1min()(1));

    EXPECT_EQ(complex_t(1.0,0.5), scrtCustom.R2plus()(0));
    EXPECT_EQ(0.0, scrtCustom.R2plus()(1));

    EXPECT_EQ(0.0, scrtCustom.R2min()(0));
    EXPECT_EQ(complex_t(0.0,0.0), scrtCustom.R2min()(1));

    EXPECT_EQ(complex_t(1.0,1.0), scrtCustom.getKz()(0));
    EXPECT_EQ(complex_t(1.0,1.0), scrtCustom.getKz()(1));

    EXPECT_EQ(complex_t(0.0,0.5), scrtCustom.getScalarT());
    EXPECT_EQ(complex_t(1.0,0.5), scrtCustom.getScalarR());
    EXPECT_EQ(complex_t(1.0,1.0), scrtCustom.getScalarKz());
}



#endif //SCALARSPECULARINFOMAPTEST_H
