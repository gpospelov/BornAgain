#include "SpecularMatrix.h"
#include "HomogeneousMagneticMaterial.h"
#include "Units.h"

class SpecularMatrixTest : public ::testing :: Test
{
protected:
    SpecularMatrixTest();
    virtual ~SpecularMatrixTest(){}
};

SpecularMatrixTest::SpecularMatrixTest() {}

TEST_F(SpecularMatrixTest, initial)
{
    MultiLayer mLayer;
    kvector_t v;
    SpecularMatrix::MultiLayerCoeff_t coeff;

    // @Error: Throws exception (Layer index is out of bounds)
    //matrix.execute(mLayer, v, coeff);


    HomogeneousMaterial air("air",0,1.0);
    Layer layer0(air, 0*Units::nanometer);
    mLayer.addLayer(layer0);

    SpecularMatrix::execute(mLayer, v, coeff);
}

TEST_F(SpecularMatrixTest, zerofield)
{
	kvector_t substr_field(0.0, 0.0, 0.0);
	HomogeneousMaterial air_material("Air", 0.0, 0.0);

	MultiLayer multi_layer_scalar;
	HomogeneousMaterial substr_material_scalar("Substrate", 7e-6, 2e-8);
	Layer air_layer(air_material);
	Layer substr_layer_scalar(substr_material_scalar);
	multi_layer_scalar.addLayer(air_layer);
	multi_layer_scalar.addLayer(substr_layer_scalar);

	MultiLayer multi_layer_zerofield;
	HomogeneousMagneticMaterial substr_material_zerofield("Substrate", 7e-6, 2e-8, substr_field);
	Layer substr_layer_zerofield(substr_material_zerofield);
	multi_layer_zerofield.addLayer(air_layer);
	multi_layer_zerofield.addLayer(substr_layer_zerofield);
}