//! Numeric tests of scalar RT computation.

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
    void printCoeffs(const std::vector<ScalarRTCoefficients>& coeffs) {
        for (size_t i=0; i<coeffs.size(); ++i) {
            const ScalarRTCoefficients& coeff = coeffs[i];
            std::cout << i << " " << coeff.t_r(0) << " " << coeff.t_r(1) << "\n";
        }
    }
    void compareCoeffs(const ScalarRTCoefficients& coeff1, const ScalarRTCoefficients& coeff2) {
        EXPECT_NEAR(abs(coeff1.t_r(0)),   abs(coeff2.t_r(0)),   1e-14);
        EXPECT_NEAR(coeff1.t_r(0).real(), coeff2.t_r(0).real(), 1e-10);
        EXPECT_NEAR(coeff1.t_r(0).imag(), coeff2.t_r(0).imag(), 1e-10);
        EXPECT_NEAR(abs(coeff1.t_r(1)),   abs(coeff2.t_r(1)),   1e-14);
        EXPECT_NEAR(coeff1.t_r(1).real(), coeff2.t_r(1).real(), 1e-10);
        EXPECT_NEAR(coeff1.t_r(1).imag(), coeff2.t_r(1).imag(), 1e-10);
    }
    const HomogeneousMaterial air {"air", 1e-8, 1e-8};
    const HomogeneousMaterial amat {"material A", 2e-6, 8e-7};
    const HomogeneousMaterial bmat {"material B (high absorption)", 3e-6, 2e-4};
    const HomogeneousMaterial stone {"substrate material", 1e-6, 1e-7};
    const Layer topLayer {air, 0};
    const Layer substrate {stone, 0};
    const kvector_t k { 1, 0, 1e-3 };
    MultiLayer sample1, sample2;
    std::vector<ScalarRTCoefficients> coeffs1, coeffs2;
};


TEST_F(RTTest, SplitLayer)
{
    const int n = 40;

    sample1.addLayer( topLayer );
    sample1.addLayer( Layer(amat, n*10) );
    sample1.addLayer( substrate );

    sample2.addLayer( topLayer );
    for (size_t i=0; i<n; ++i)
        sample2.addLayer( Layer(amat, 10) );
    sample2.addLayer( substrate );

    SpecularMatrix::execute(sample1, k, coeffs1);
    SpecularMatrix::execute(sample2, k, coeffs2);

    // printCoeffs( coeffs1 );
    // printCoeffs( coeffs2 );

    compareCoeffs(coeffs1[0], coeffs2[0]);
    compareCoeffs(coeffs1[1], coeffs2[1]);
    compareCoeffs(coeffs1.back(), coeffs2.back());
}
