#ifndef MATRIXSPECULARINFOMAPTEST_H
#define MATRIXSPECULARINFOMAPTEST_H

#include "HomogeneousMaterial.h"
#include "Layer.h"
#include "MatrixRTCoefficients.h"
#include "MatrixSpecularInfoMap.h"
#include "MultiLayer.h"
#include "MathConstants.h"
#include "SimulationElement.h"
#include <memory>

class MatrixSpecularInfoMapTest : public ::testing :: Test
{
protected:
    MatrixSpecularInfoMapTest();
    virtual ~MatrixSpecularInfoMapTest() {
        delete mp_multilayer;
    }
    MultiLayer* mp_multilayer;
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
    MatrixSpecularInfoMap map(mp_multilayer, 0);
    SimulationElement sim_element(M_TWOPI, 1.0, 1.0, nullptr);
    std::unique_ptr<const MatrixRTCoefficients> P_rt_coeffs(
                (MatrixRTCoefficients*) map.getOutCoefficients(sim_element));
    complex_t R0 = complex_t(0.1750375, -0.0222467);
    complex_t lambda0 = complex_t(0.841471, 0.0);
    (void)R0;
    (void)lambda0;

    EXPECT_TRUE(nullptr != P_rt_coeffs.get());

    EXPECT_EQ(0.0, P_rt_coeffs->T1plus()(0));
    EXPECT_EQ(0.0, P_rt_coeffs->T1plus()(1));

    EXPECT_EQ(0.0, P_rt_coeffs->T1min()(0));
    EXPECT_NEAR(1.0, P_rt_coeffs->T1min()(1).real(), 1e-6);
    EXPECT_NEAR(0.0, P_rt_coeffs->T1min()(1).imag(), 1e-6);

    EXPECT_NEAR(1.0, P_rt_coeffs->T2plus()(0).real(), 1e-6);
    EXPECT_NEAR(0.0, P_rt_coeffs->T2plus()(0).imag(), 1e-6);
    EXPECT_EQ(0.0, P_rt_coeffs->T2plus()(1));

    EXPECT_EQ(0.0, P_rt_coeffs->T2min()(0));
    EXPECT_EQ(0.0, P_rt_coeffs->T2min()(1));

    EXPECT_EQ(0.0, P_rt_coeffs->R1plus()(0));
    EXPECT_EQ(0.0, P_rt_coeffs->R1plus()(1));

    EXPECT_EQ(0.0, P_rt_coeffs->R1min()(0));
    EXPECT_NEAR(R0.real(), P_rt_coeffs->R1min()(1).real(), 1e-6);
    EXPECT_NEAR(R0.imag(), P_rt_coeffs->R1min()(1).imag(), 1e-6);

    EXPECT_NEAR(R0.real(), P_rt_coeffs->R2plus()(0).real(), 1e-6);
    EXPECT_NEAR(R0.imag(), P_rt_coeffs->R2plus()(0).imag(), 1e-6);
    EXPECT_EQ(0.0, P_rt_coeffs->R2plus()(1));

    EXPECT_EQ(0.0, P_rt_coeffs->R2min()(0));
    EXPECT_EQ(0.0, P_rt_coeffs->R2min()(1));

    EXPECT_NEAR(lambda0.real(), P_rt_coeffs->getKz()(0).real(), 1e-6);
    EXPECT_NEAR(lambda0.imag(), P_rt_coeffs->getKz()(0).imag(), 1e-6);
    EXPECT_NEAR(lambda0.real(), P_rt_coeffs->getKz()(1).real(), 1e-6);
    EXPECT_NEAR(lambda0.imag(), P_rt_coeffs->getKz()(1).imag(), 1e-6);
}

#endif // MATRIXSPECULARINFOMAPTEST_H
