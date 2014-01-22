#ifndef MATRIXSPECULARINFOMAPTEST_H
#define MATRIXSPECULARINFOMAPTEST_H

#include "MatrixRTCoefficients.h"
#include "MatrixSpecularInfoMap.h"
#include "gtest/gtest.h"


class MatrixSpecularInfoMapTest : public ::testing :: Test
{
protected:
    MatrixSpecularInfoMapTest();
    virtual ~MatrixSpecularInfoMapTest(){}

    MatrixRTCoefficients mrtcDefault;
    MatrixSpecularInfoMap map;
};

MatrixSpecularInfoMapTest::MatrixSpecularInfoMapTest()
{
    map.addCoefficients(* new MatrixRTCoefficients(), 1.0, 1.0);

    mrtcDefault = * map.getCoefficients(1.0, 1.0);
}

TEST_F(MatrixSpecularInfoMapTest, getCoeffiecients)
{
    EXPECT_TRUE(NULL != map.getCoefficients(1.0, 1.0));


    EXPECT_EQ(complex_t(0.5,0.0), mrtcDefault.T1plus()(0));
    EXPECT_EQ(0.0, mrtcDefault.T1plus()(1));

    EXPECT_EQ(0.0, mrtcDefault.T1min()(0));
    EXPECT_EQ(complex_t(0.5,0.0), mrtcDefault.T1min()(1));


    EXPECT_EQ(complex_t(0.5,0.0), mrtcDefault.T2plus()(0));
    EXPECT_EQ(0.0, mrtcDefault.T2plus()(1));

    EXPECT_EQ(0.0, mrtcDefault.T2min()(0));
    EXPECT_EQ(complex_t(0.5,0.0), mrtcDefault.T2min()(1));

    EXPECT_EQ(complex_t(-0.5,0.0), mrtcDefault.R1plus()(0));
    EXPECT_EQ(0.0, mrtcDefault.R1plus()(1));

    EXPECT_EQ(0.0, mrtcDefault.R1min()(0));
    EXPECT_EQ(complex_t(-0.5,0.0), mrtcDefault.R1min()(1));

    EXPECT_EQ(complex_t(-0.5,0.0), mrtcDefault.R2plus()(0));
    EXPECT_EQ(0.0, mrtcDefault.R2plus()(1));

    EXPECT_EQ(0.0, mrtcDefault.R2min()(0));
    EXPECT_EQ(complex_t(-0.5,0.0), mrtcDefault.R2min()(1));

    EXPECT_EQ(complex_t(0.0,0.0), mrtcDefault.getKz()(0));
    EXPECT_EQ(complex_t(0.0,0.0), mrtcDefault.getKz()(1));
}



#endif //MATRIXSPECULARINFOMAPTEST_H

