#include "google_test.h"
#include "Layer.h"
#include "MultiLayer.h"
#include "MaterialFactoryFuncs.h"
#include "SpecularMatrix.h"
#include "Units.h"

class SpecularMatrixTest : public ::testing::Test
{
protected:
    ~SpecularMatrixTest();
};

SpecularMatrixTest::~SpecularMatrixTest() = default;

TEST_F(SpecularMatrixTest, initial)
{
    MultiLayer mLayer;
    kvector_t v;

    // @Error: Throws exception (Layer index is out of bounds)
    // matrix.execute(mLayer, v, coeff);

    Layer layer0(HomogeneousMaterial("air", 0, 1.0), 0 * Units::nanometer);
    mLayer.addLayer(layer0);

    std::vector<ScalarRTCoefficients> coeff = SpecularMatrix::execute(mLayer, v);
}
