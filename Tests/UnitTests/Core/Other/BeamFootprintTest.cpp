#include "Core/Beam/Beam.h"
#include "Core/Beam/FootprintFactorGaussian.h"
#include "Core/Beam/FootprintFactorSquare.h"
#include "Core/Parametrization/Units.h"
#include "Tests/GTestWrapper/google_test.h"

#include <limits>
#include <memory>

class BeamFootprintTest : public ::testing::Test
{
};

TEST_F(BeamFootprintTest, ErroneousArguments)
{
    EXPECT_THROW(std::make_unique<FootprintFactorGaussian>(-1.0), std::runtime_error);
    EXPECT_THROW(std::make_unique<FootprintFactorSquare>(-1.0), std::runtime_error);

    FootprintFactorGaussian gaussian_ff(std::numeric_limits<double>::infinity());
    EXPECT_EQ(0.0, gaussian_ff.calculate(-90.0 * Units::deg));

    FootprintFactorSquare square_ff(std::numeric_limits<double>::infinity());
    EXPECT_EQ(0.0, square_ff.calculate(-90.0 * Units::deg));
}

TEST_F(BeamFootprintTest, CalcForCornerCases)
{
    FootprintFactorGaussian gaussian_ff(0.0);
    EXPECT_EQ(1.0, gaussian_ff.calculate(0.0));
    EXPECT_EQ(1.0, gaussian_ff.calculate(90.0 * Units::deg));

    FootprintFactorSquare square_ff(0.0);
    EXPECT_EQ(1.0, square_ff.calculate(0.0));
    EXPECT_EQ(1.0, square_ff.calculate(90.0 * Units::deg));

    FootprintFactorGaussian gaussian_ff2(std::numeric_limits<double>::infinity());

    EXPECT_EQ(0.0, gaussian_ff2.calculate(0.0));
    EXPECT_EQ(0.0, gaussian_ff2.calculate(90.0 * Units::deg));

    FootprintFactorSquare square_ff2(std::numeric_limits<double>::infinity());

    EXPECT_EQ(0.0, square_ff2.calculate(0.0));
    EXPECT_EQ(0.0, square_ff2.calculate(90.0 * Units::deg));
}

TEST_F(BeamFootprintTest, CalcForRegularCases)
{
    FootprintFactorGaussian gaussian_ff(1.0 / std::sqrt(2.0));

    EXPECT_EQ(0.0, gaussian_ff.calculate(0.0));
    EXPECT_NEAR(0.84270079295, gaussian_ff.calculate(90.0 * Units::deg), 1e-10);

    FootprintFactorSquare square_ff(2.0);

    EXPECT_EQ(0.0, square_ff.calculate(0.0));
    EXPECT_EQ(0.5, square_ff.calculate(90.0 * Units::deg));
}

TEST_F(BeamFootprintTest, Clone)
{
    FootprintFactorGaussian gaussian_ff(1.0);
    std::unique_ptr<FootprintFactorGaussian> gaussian_clone(gaussian_ff.clone());

    EXPECT_NE(gaussian_clone.get(), &gaussian_ff);
    EXPECT_EQ(gaussian_clone->widthRatio(), gaussian_ff.widthRatio());

    FootprintFactorSquare square_ff(1.0);
    std::unique_ptr<FootprintFactorSquare> square_clone(square_ff.clone());

    EXPECT_NE(square_clone.get(), &square_ff);
    EXPECT_EQ(square_clone->widthRatio(), square_ff.widthRatio());
}
