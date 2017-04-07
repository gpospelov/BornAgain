#include "SpecularMatrix.h"
#include "SpecularMagnetic.h"
#include "HomogeneousMaterial.h"
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
    std::vector<MatrixRTCoefficients> coeff;

    // @Error: Throws exception (Layer index is out of bounds)
    //matrix.execute(mLayer, v, coeff);


    HomogeneousMaterial air("air",0,1.0);
    Layer layer0(air, 0*Units::nanometer);
    mLayer.addLayer(layer0);

    SpecularMagnetic::execute(mLayer, v, coeff);
}

TEST_F(SpecularMagneticTest, zerofield)
{
    double eps = 1e-10;

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
    std::vector<ScalarRTCoefficients> coeffs_scalar;

    MultiLayer multi_layer_zerofield;
    HomogeneousMaterial substr_material_zerofield("Substrate", 7e-6, 2e-8, substr_field);
    Layer substr_layer_zerofield(substr_material_zerofield);
    multi_layer_zerofield.addLayer(air_layer);
    multi_layer_zerofield.addLayer(substr_layer_zerofield);
    std::vector<MatrixRTCoefficients> coeffs_zerofield;

    // k1
    SpecularMatrix::execute(multi_layer_scalar, k1, coeffs_scalar);
    ScalarRTCoefficients RTScalar = coeffs_scalar[1];
    Eigen::Vector2cd TPS = RTScalar.T1plus() + RTScalar.T2plus();
    Eigen::Vector2cd RPS = RTScalar.R1plus() + RTScalar.R2plus();
    Eigen::Vector2cd TMS = RTScalar.T1min() + RTScalar.T2min();
    Eigen::Vector2cd RMS = RTScalar.R1min() + RTScalar.R2min();

    SpecularMagnetic::execute(multi_layer_zerofield, k1, coeffs_zerofield);
    MatrixRTCoefficients RTMatrix = coeffs_zerofield[1];
    Eigen::Vector2cd TPM = RTMatrix.T1plus() + RTMatrix.T2plus();
    Eigen::Vector2cd RPM = RTMatrix.R1plus() + RTMatrix.R2plus();
    Eigen::Vector2cd TMM = RTMatrix.T1min() + RTMatrix.T2min();
    Eigen::Vector2cd RMM = RTMatrix.R1min() + RTMatrix.R2min();

    EXPECT_NEAR(0.0, std::abs(TPS(0)-TPM(0)), eps);
    EXPECT_NEAR(0.0, std::abs(TPS(1)-TPM(1)), eps);
    EXPECT_NEAR(0.0, std::abs(RPS(0)-RPM(0)), eps);
    EXPECT_NEAR(0.0, std::abs(RPS(1)-RPM(1)), eps);
    EXPECT_NEAR(0.0, std::abs(TMS(0)-TMM(0)), eps);
    EXPECT_NEAR(0.0, std::abs(TMS(1)-TMM(1)), eps);
    EXPECT_NEAR(0.0, std::abs(RMS(0)-RMM(0)), eps);
    EXPECT_NEAR(0.0, std::abs(RMS(1)-RMM(1)), eps);

    // k2
    SpecularMatrix::execute(multi_layer_scalar, k2, coeffs_scalar);
    RTScalar = coeffs_scalar[1];
    TPS = RTScalar.T1plus() + RTScalar.T2plus();
    RPS = RTScalar.R1plus() + RTScalar.R2plus();
    TMS = RTScalar.T1min() + RTScalar.T2min();
    RMS = RTScalar.R1min() + RTScalar.R2min();

    SpecularMagnetic::execute(multi_layer_zerofield, k2, coeffs_zerofield);
    RTMatrix = coeffs_zerofield[1];
    TPM = RTMatrix.T1plus() + RTMatrix.T2plus();
    RPM = RTMatrix.R1plus() + RTMatrix.R2plus();
    TMM = RTMatrix.T1min() + RTMatrix.T2min();
    RMM = RTMatrix.R1min() + RTMatrix.R2min();

    EXPECT_NEAR(0.0, std::abs(TPS(0)-TPM(0)), eps);
    EXPECT_NEAR(0.0, std::abs(TPS(1)-TPM(1)), eps);
    EXPECT_NEAR(0.0, std::abs(RPS(0)-RPM(0)), eps);
    EXPECT_NEAR(0.0, std::abs(RPS(1)-RPM(1)), eps);
    EXPECT_NEAR(0.0, std::abs(TMS(0)-TMM(0)), eps);
    EXPECT_NEAR(0.0, std::abs(TMS(1)-TMM(1)), eps);
    EXPECT_NEAR(0.0, std::abs(RMS(0)-RMM(0)), eps);
    EXPECT_NEAR(0.0, std::abs(RMS(1)-RMM(1)), eps);

    // k3
    SpecularMatrix::execute(multi_layer_scalar, k3, coeffs_scalar);
    RTScalar = coeffs_scalar[1];
    TPS = RTScalar.T1plus() + RTScalar.T2plus();
    RPS = RTScalar.R1plus() + RTScalar.R2plus();
    TMS = RTScalar.T1min() + RTScalar.T2min();
    RMS = RTScalar.R1min() + RTScalar.R2min();

    SpecularMagnetic::execute(multi_layer_zerofield, k3, coeffs_zerofield);
    RTMatrix = coeffs_zerofield[1];
    TPM = RTMatrix.T1plus() + RTMatrix.T2plus();
    RPM = RTMatrix.R1plus() + RTMatrix.R2plus();
    TMM = RTMatrix.T1min() + RTMatrix.T2min();
    RMM = RTMatrix.R1min() + RTMatrix.R2min();

    EXPECT_NEAR(0.0, std::abs(TPS(0)-TPM(0)), eps);
    EXPECT_NEAR(0.0, std::abs(TPS(1)-TPM(1)), eps);
    EXPECT_NEAR(0.0, std::abs(RPS(0)-RPM(0)), eps);
    EXPECT_NEAR(0.0, std::abs(RPS(1)-RPM(1)), eps);
    EXPECT_NEAR(0.0, std::abs(TMS(0)-TMM(0)), eps);
    EXPECT_NEAR(0.0, std::abs(TMS(1)-TMM(1)), eps);
    EXPECT_NEAR(0.0, std::abs(RMS(0)-RMM(0)), eps);
    EXPECT_NEAR(0.0, std::abs(RMS(1)-RMM(1)), eps);
}
