#include "FootprintFactorGaussian.h"
#include "FootprintFactorSquare.h"
#include "MultiLayer.h"
#include "Units.h"
#include "google_test.h"

#include <limits>
#include <memory>

class BeamFootprintTest : public ::testing::Test
{
protected:
    template<class FFType>
    std::unique_ptr<FFType> createFootprintFactor(double beam_width)
    {
        return std::make_unique<FFType>(beam_width);
    }

    void setScale(double value) {mLayer.setScale(value);}

    MultiLayer mLayer;
};

TEST_F(BeamFootprintTest, DefaultState)
{
    FootprintFactorGaussian gaussian_ff(0.0);
    EXPECT_EQ(1.0, gaussian_ff.calculate(mLayer, 0.0));
    EXPECT_EQ(1.0, gaussian_ff.calculate(mLayer, 90.0 * Units::deg));

    FootprintFactorGaussian gaussian_ff2(2.0);
    EXPECT_EQ(1.0, gaussian_ff2.calculate(mLayer, 0.0));
    EXPECT_EQ(1.0, gaussian_ff2.calculate(mLayer, 90.0 * Units::deg));

    FootprintFactorSquare square_ff(0.0);
    EXPECT_EQ(1.0, square_ff.calculate(mLayer, 0.0));
    EXPECT_EQ(1.0, square_ff.calculate(mLayer, 90.0 * Units::deg));

    FootprintFactorSquare square_ff2(2.0);
    EXPECT_EQ(1.0, square_ff2.calculate(mLayer, 0.0));
    EXPECT_EQ(1.0, square_ff2.calculate(mLayer, 90.0 * Units::deg));
}

TEST_F(BeamFootprintTest, ErroneousArguments)
{
    EXPECT_THROW(createFootprintFactor<FootprintFactorGaussian>(-1.0), std::runtime_error);
    EXPECT_THROW(createFootprintFactor<FootprintFactorSquare>(-1.0), std::runtime_error);

    setScale(1.0);

    FootprintFactorGaussian gaussian_ff(std::numeric_limits<double>::infinity());
    EXPECT_THROW(gaussian_ff.calculate(mLayer, -90.0 * Units::deg), std::runtime_error);

    FootprintFactorSquare square_ff(std::numeric_limits<double>::infinity());
    EXPECT_THROW(square_ff.calculate(mLayer, -90.0 * Units::deg), std::runtime_error);
}

TEST_F(BeamFootprintTest, CornerCases)
{
    setScale(1.0);

    FootprintFactorGaussian gaussian_ff(std::numeric_limits<double>::infinity());

    EXPECT_EQ(0.0, gaussian_ff.calculate(mLayer, 0.0));
    EXPECT_EQ(0.0, gaussian_ff.calculate(mLayer, 90.0 * Units::deg));

    FootprintFactorSquare square_ff(std::numeric_limits<double>::infinity());

    EXPECT_EQ(0.0, square_ff.calculate(mLayer, 0.0));
    EXPECT_EQ(0.0, square_ff.calculate(mLayer, 90.0 * Units::deg));

    setScale(std::numeric_limits<double>::infinity());

    FootprintFactorGaussian gaussian_ff2(0.0);

    EXPECT_EQ(1.0, gaussian_ff2.calculate(mLayer, 0.0));
    EXPECT_EQ(1.0, gaussian_ff2.calculate(mLayer, 90.0 * Units::deg));

    FootprintFactorSquare square_ff2(0.0);

    EXPECT_EQ(1.0, square_ff2.calculate(mLayer, 0.0));
    EXPECT_EQ(1.0, square_ff2.calculate(mLayer, 90.0 * Units::deg));
}

TEST_F(BeamFootprintTest, RegularCases)
{
    setScale(1.0);

    FootprintFactorGaussian gaussian_ff(1. / std::sqrt(2.0));

    EXPECT_EQ(0.0, gaussian_ff.calculate(mLayer, 0.0));
    EXPECT_NEAR(0.84270079295, gaussian_ff.calculate(mLayer, 90.0 * Units::deg), 1e-10);

    FootprintFactorSquare square_ff(2.0);

    EXPECT_EQ(0.0, square_ff.calculate(mLayer, 0.0));
    EXPECT_EQ(0.5, square_ff.calculate(mLayer, 90.0 * Units::deg));
}
