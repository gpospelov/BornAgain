//! Numeric tests of RT computation.

#include "BornAgainNamespace.h"
#include "HomogeneousMagneticMaterial.h"
#include "Layer.h"
#include "Layer.h"
#include "LayerInterface.h"
#include "LayerRoughness.h"
#include "MathConstants.h"
#include "MultiLayer.h"
#include "ParticleLayout.h"
#include "SpecularMatrix.h"

#include <iostream> // TODO remove when stable

class RTTest : public ::testing::Test
{
protected:
    RTTest() {}
    void set_four() {
        sample1.addLayer(topLayer);
        sample1.addLayer( Layer(amat, 10) );
        sample1.addLayer( Layer(bmat, 20) );
        sample1.addLayer(substrate);
    }
    void printCoeffs(const std::vector<ScalarRTCoefficients>& coeffs) {
        for (size_t i=0; i<coeffs.size(); ++i) {
            const ScalarRTCoefficients& coeff = coeffs[i];
            std::cout << i << " " << coeff.t_r(0) << " " << coeff.t_r(1) << "\n";
        }
    }
    const HomogeneousMaterial air {"air", 1e-8, 1e-8};
    const HomogeneousMaterial amat {"material A", 2e-6, 8e-7};
    const HomogeneousMaterial bmat {"material B (high absorption)", 3e-6, 1e-4};
    const HomogeneousMaterial stone {"substrate material", 1e-6, 1e-7};
    const Layer topLayer {air, 0};
    const Layer substrate {stone, 0};
    const kvector_t k { 1, 0, 1e-2 };
    MultiLayer sample1, sample2;
    std::vector<ScalarRTCoefficients> coeffs1, coeffs2;
};


TEST_F(RTTest, BasicProperty)
{
    sample1.addLayer( topLayer );
    sample1.addLayer( Layer(amat, 10) );
    sample1.addLayer( Layer(amat, 10) );
    sample1.addLayer( substrate );

    sample2.addLayer( topLayer );
    sample2.addLayer( Layer(amat, 20) );
    sample2.addLayer( substrate );

    SpecularMatrix::execute(sample1, k, coeffs1);
    SpecularMatrix::execute(sample2, k, coeffs2);

    printCoeffs( coeffs1 );
    printCoeffs( coeffs2 );

    EXPECT_EQ(1,1);
}
