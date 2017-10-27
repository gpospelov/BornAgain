#include "SpecularMatrix.h"
#include "MaterialFactoryFuncs.h"
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
    std::vector<ScalarRTCoefficients> coeff;

    // @Error: Throws exception (Layer index is out of bounds)
    //matrix.execute(mLayer, v, coeff);

    Layer layer0(HomogeneousMaterial("air",0,1.0), 0*Units::nanometer);
    mLayer.addLayer(layer0);

    SpecularMatrix::execute(mLayer, v, coeff);
}
