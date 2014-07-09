#ifndef MATRIXSPECULARINFOMAPTEST_H
#define MATRIXSPECULARINFOMAPTEST_H

#include "MatrixRTCoefficients.h"
#include "MatrixSpecularInfoMap.h"
#include "gtest/gtest.h"

#include <boost/scoped_ptr.hpp>

class MatrixSpecularInfoMapTest : public ::testing :: Test
{
protected:
    MatrixSpecularInfoMapTest();
    virtual ~MatrixSpecularInfoMapTest() {
        delete mp_multilayer;
    }

    MultiLayer *mp_multilayer;
};

MatrixSpecularInfoMapTest::MatrixSpecularInfoMapTest()
{
    mp_multilayer = new MultiLayer;

    HomogeneousMaterial air_material("Air", 0., 0.);
    HomogeneousMaterial substrate_material("Substrate", 0.2, 0.02);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    mp_multilayer->addLayer(air_layer);
    mp_multilayer->addLayer(substrate_layer);
}

TEST_F(MatrixSpecularInfoMapTest, getCoefficients)
{
    MatrixSpecularInfoMap map(mp_multilayer, 0, 2.0*M_PI);
    boost::scoped_ptr<const MatrixRTCoefficients> rt_coeffs(
                map.getCoefficients(1.0, 1.0));
    complex_t R0 = complex_t(0.1750375, -0.0222467);
    complex_t lambda0 = complex_t(0.841471, 0.0);
    (void)R0;
    (void)lambda0;

    EXPECT_TRUE(NULL != rt_coeffs.get());

    EXPECT_EQ(0.0, rt_coeffs->T1plus()(0));
    EXPECT_EQ(0.0, rt_coeffs->T1plus()(1));

//    EXPECT_EQ(0.0, rt_coeffs->T1min()(0));
//    EXPECT_EQ(complex_t(0.5,0.0), rt_coeffs->T1min()(1));

//    EXPECT_EQ(complex_t(0.5,0.0), rt_coeffs->T2plus()(0));
//    EXPECT_EQ(0.0, rt_coeffs->T2plus()(1));

//    EXPECT_EQ(0.0, rt_coeffs->T2min()(0));
//    EXPECT_EQ(complex_t(0.5,0.0), rt_coeffs->T2min()(1));

//    EXPECT_EQ(complex_t(-0.5,0.0), rt_coeffs->R1plus()(0));
//    EXPECT_EQ(0.0, rt_coeffs->R1plus()(1));

//    EXPECT_EQ(0.0, rt_coeffs->R1min()(0));
//    EXPECT_EQ(complex_t(-0.5,0.0), rt_coeffs->R1min()(1));

//    EXPECT_EQ(complex_t(-0.5,0.0), rt_coeffs->R2plus()(0));
//    EXPECT_EQ(0.0, rt_coeffs->R2plus()(1));

//    EXPECT_EQ(0.0, rt_coeffs->R2min()(0));
//    EXPECT_EQ(complex_t(-0.5,0.0), rt_coeffs->R2min()(1));

//    EXPECT_EQ(complex_t(0.0,0.0), rt_coeffs->getKz()(0));
//    EXPECT_EQ(complex_t(0.0,0.0), rt_coeffs->getKz()(1));
}

#endif //MATRIXSPECULARINFOMAPTEST_H

