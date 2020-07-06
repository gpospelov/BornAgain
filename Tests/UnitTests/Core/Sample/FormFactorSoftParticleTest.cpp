#include "Core/Basics/Exceptions.h"
#include "Core/includeIncludes/SoftParticles.h"
#include "Tests/UnitTests/utilities/google_test.h"

class FormFactorSoftParticleTest : public ::testing::Test
{
};

TEST_F(FormFactorSoftParticleTest, FormFactorOrnsteinZernike)
{
    const double epsilon = 1e-12;
    auto ff = new FormFactorOrnsteinZernike(1.0, 3.0, 2.0);
    complex_t ff0 = ff->evaluate_for_q(cvector_t(0.0, 0.0, 0.0));
    EXPECT_NEAR(1.0, ff0.real(), epsilon);
    EXPECT_NEAR(0.0, ff0.imag(), epsilon);
    complex_t ff1 = ff->evaluate_for_q(cvector_t(0.0, 1.0, 0.0));
    EXPECT_NEAR(sqrt(0.1), ff1.real(), epsilon);
    EXPECT_NEAR(0.0, ff1.imag(), epsilon);
    complex_t ff2 = ff->evaluate_for_q(cvector_t(0.0, 0.0, 1.0));
    EXPECT_NEAR(sqrt(0.2), ff2.real(), epsilon);
    EXPECT_NEAR(0.0, ff2.imag(), epsilon);
    complex_t ff3 = ff->evaluate_for_q(cvector_t(0.1, 0.2, 0.3));
    EXPECT_NEAR(sqrt(1.0 / 1.81), ff3.real(), epsilon);
    EXPECT_NEAR(0.0, ff3.imag(), epsilon);
}

TEST_F(FormFactorSoftParticleTest, FormFactorDebyeBueche)
{
    const double epsilon = 1e-12;
    auto ff = new FormFactorDebyeBueche(4.0, 3.0);
    complex_t ff0 = ff->evaluate_for_q(cvector_t(0.0, 0.0, 0.0));
    EXPECT_NEAR(2.0, ff0.real(), epsilon);
    EXPECT_NEAR(0.0, ff0.imag(), epsilon);
    complex_t ff1 = ff->evaluate_for_q(cvector_t(0.0, 1.0, 0.0));
    EXPECT_NEAR(0.2, ff1.real(), epsilon);
    EXPECT_NEAR(0.0, ff1.imag(), epsilon);
    complex_t ff2 = ff->evaluate_for_q(cvector_t(0.0, 0.0, 1.0));
    EXPECT_NEAR(0.2, ff2.real(), epsilon);
    EXPECT_NEAR(0.0, ff2.imag(), epsilon);
    complex_t ff3 = ff->evaluate_for_q(cvector_t(0.1, 0.2, 0.3));
    EXPECT_NEAR(2.0 / 2.26, ff3.real(), epsilon);
    EXPECT_NEAR(0.0, ff3.imag(), epsilon);
}
