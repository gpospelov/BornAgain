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
    kvector_t k(3.0, 0.0, -0.1);

    MultiLayer multi_layer_scalar;
    HomogeneousMaterial substr_material_scalar("Substrate", 7e-6, 2e-8);
    Layer air_layer(air_material);
    Layer substr_layer_scalar(substr_material_scalar);
    multi_layer_scalar.addLayer(air_layer);
    multi_layer_scalar.addLayer(substr_layer_scalar);
    SpecularMatrix::MultiLayerCoeff_t coeffs_scalar;
    SpecularMatrix::execute(multi_layer_scalar, k, coeffs_scalar);

    MultiLayer multi_layer_zerofield;
    HomogeneousMagneticMaterial substr_material_zerofield("Substrate", 7e-6, 2e-8, substr_field);
    Layer substr_layer_zerofield(substr_material_zerofield);
    multi_layer_zerofield.addLayer(air_layer);
    multi_layer_zerofield.addLayer(substr_layer_zerofield);
    SpecularMagnetic::MultiLayerCoeff_t coeffs_zerofield;
    SpecularMagnetic::execute(multi_layer_zerofield, k, coeffs_zerofield);
}
