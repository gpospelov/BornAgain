#include "google_test.h"
#include "SpecularSimulationElement.h"

class SpecularSimulationElementTest : public ::testing::Test
{
protected:
    SpecularSimulationElementTest();
    ~SpecularSimulationElementTest();

    SpecularSimulationElement createDefaultElement();

    void compareElements(const SpecularSimulationElement& lhs,
                         const SpecularSimulationElement& rhs);

    PolarizationHandler test_polarization;
    Eigen::Matrix2cd identity;
};

SpecularSimulationElementTest::SpecularSimulationElementTest()
    : identity(Eigen::Matrix2cd::Identity())
{
    Eigen::Matrix2cd polarization;
    polarization << 0, 1,
                    1, 0;
    test_polarization.setPolarization(polarization);
}

SpecularSimulationElementTest::~SpecularSimulationElementTest() = default;

SpecularSimulationElement SpecularSimulationElementTest::createDefaultElement()
{
    const double wavelength = 1.0;
    const double angle = 2.0;
    return SpecularSimulationElement(wavelength, angle);
}

void SpecularSimulationElementTest::compareElements(const SpecularSimulationElement& lhs,
                                                    const SpecularSimulationElement& rhs)
{
    EXPECT_EQ(lhs.polarizationHandler().getPolarization(),
              rhs.polarizationHandler().getPolarization());
    EXPECT_EQ(rhs.polarizationHandler().getPolarization(), test_polarization.getPolarization());
    EXPECT_EQ(lhs.getWavelength(), rhs.getWavelength());
    EXPECT_EQ(lhs.getAlphaI(), rhs.getAlphaI());
    EXPECT_EQ(lhs.getIntensity(), rhs.getIntensity());
    EXPECT_EQ(lhs.getKi(), rhs.getKi());
    EXPECT_EQ(lhs.isCalculated(), rhs.isCalculated());
}

TEST_F(SpecularSimulationElementTest, InitialState)
{
    const double wavelength = 1.0;
    const double angle = 2.0;
    const double phi = 0.0;
    const kvector_t k_i = vecOfLambdaAlphaPhi(wavelength, angle, phi);
    const SpecularSimulationElement& element = createDefaultElement();

    EXPECT_EQ(wavelength, element.getWavelength());
    EXPECT_EQ(angle, element.getAlphaI());
    EXPECT_EQ(0.0, element.getIntensity());
    EXPECT_EQ(k_i, element.getKi());
    EXPECT_TRUE(element.isCalculated());

    EXPECT_EQ(identity, element.polarizationHandler().getPolarization());
    EXPECT_EQ(identity, element.polarizationHandler().getAnalyzerOperator());
}

TEST_F(SpecularSimulationElementTest, CopyMoveAssign)
{
    auto element = createDefaultElement();

    element.setPolarizationHandler(test_polarization);
    element.setCalculationFlag(false);

    SpecularSimulationElement element2 = element;

    compareElements(element, element2);

    auto element3 = createDefaultElement();
    element3 = element;

    compareElements(element, element3);

    auto element4 = std::move(element);

    compareElements(element2, element4);

    auto element5 = createDefaultElement();
    element5 = std::move(element2);

    compareElements(element5, element3);
}
