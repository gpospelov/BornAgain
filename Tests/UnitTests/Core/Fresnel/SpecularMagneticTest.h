#include "SpecularMatrix.h"
#include "SpecularMagnetic.h"
#include "HomogeneousMagneticMaterial.h"
#include "Units.h"

class SpecularMagneticTest : public ::testing :: Test
{
protected:
    SpecularMagneticTest();
    virtual ~SpecularMagneticTest(){}
};

SpecularMagneticTest::SpecularMagneticTest() {}

TEST_F(SpecularMagneticTest, initial)
{
    MultiLayer mLayer;
    kvector_t v;
    SpecularMagnetic::MultiLayerCoeff_t coeff;

    // @Error: Throws exception (Layer index is out of bounds)
    //matrix.execute(mLayer, v, coeff);


    HomogeneousMaterial air("air",0,1.0);
    Layer layer0(air, 0*Units::nanometer);
    mLayer.addLayer(layer0);

    SpecularMagnetic::execute(mLayer, v, coeff);
}

TEST_F(SpecularMagneticTest, zerofield)
{
    kvector_t substr_field(0.0, 0.0, 0.0);
    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    kvector_t k1 = vecOfLambdaAlphaPhi(1.0, -0.1*Units::deg, 0.0);
    kvector_t k2 = vecOfLambdaAlphaPhi(1.0, -2.0*Units::deg, 0.0);
    kvector_t k3 = vecOfLambdaAlphaPhi(1.0, -10.0*Units::deg, 0.0);

    MultiLayer multi_layer_scalar;
    HomogeneousMaterial substr_material_scalar("Substrate", 7e-6, 2e-8);
    Layer air_layer(air_material);
    Layer substr_layer_scalar(substr_material_scalar);
    multi_layer_scalar.addLayer(air_layer);
    multi_layer_scalar.addLayer(substr_layer_scalar);
    SpecularMatrix::MultiLayerCoeff_t coeffs_scalar;
    SpecularMatrix::execute(multi_layer_scalar, k1, coeffs_scalar);
    ScalarRTCoefficients RTScalar1 = coeffs_scalar[1];
    Eigen::Vector2cd TPS = RTScalar1.T1plus() + RTScalar1.T2plus();
    Eigen::Vector2cd RPS = RTScalar1.R1plus() + RTScalar1.R2plus();
    Eigen::Vector2cd TMS = RTScalar1.T1min() + RTScalar1.T2min();
    Eigen::Vector2cd RMS = RTScalar1.R1min() + RTScalar1.R2min();

    MultiLayer multi_layer_zerofield;
    HomogeneousMagneticMaterial substr_material_zerofield("Substrate", 7e-6, 2e-8, substr_field);
    Layer substr_layer_zerofield(substr_material_zerofield);
    multi_layer_zerofield.addLayer(air_layer);
    multi_layer_zerofield.addLayer(substr_layer_zerofield);
    SpecularMagnetic::MultiLayerCoeff_t coeffs_zerofield;
    SpecularMagnetic::execute(multi_layer_zerofield, k1, coeffs_zerofield);
    MatrixRTCoefficients RTMatrix1 = coeffs_zerofield[1];
    Eigen::Vector2cd TPM = RTMatrix1.T1plus() + RTMatrix1.T2plus();
    Eigen::Vector2cd RPM = RTMatrix1.R1plus() + RTMatrix1.R2plus();
    Eigen::Vector2cd TMM = RTMatrix1.T1min() + RTMatrix1.T2min();
    Eigen::Vector2cd RMM = RTMatrix1.R1min() + RTMatrix1.R2min();

    EXPECT_EQ(TPS(0), TPM(0));
    EXPECT_EQ(TPS(1), TPM(1));
    EXPECT_EQ(RPS(0), RPM(0));
    EXPECT_EQ(RPS(1), RPM(1));
    EXPECT_EQ(TMS(0), TMM(0));
    EXPECT_EQ(TMS(1), TMM(1));
    EXPECT_EQ(RMS(0), RMM(0));
    EXPECT_EQ(RMS(1), RMM(1));
}
