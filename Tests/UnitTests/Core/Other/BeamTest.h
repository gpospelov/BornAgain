#include "Beam.h"
#include "BornAgainNamespace.h"
#include "FootprintFactorSquare.h"
#include "MathConstants.h"
#include "ParameterPool.h"
#include "RealParameter.h"
#include "google_test.h"

#include <memory>
#include <typeinfo>

class BeamTest : public ::testing::Test
{
protected:
    ~BeamTest();

    Beam m_empty_beam;
};

BeamTest::~BeamTest() = default;

TEST_F(BeamTest, BeamInitialState)
{
    EXPECT_DOUBLE_EQ(M_TWOPI, m_empty_beam.getCentralK()[0]);
    EXPECT_EQ(0.0, m_empty_beam.getCentralK()[1]);
    EXPECT_EQ(0.0, m_empty_beam.getCentralK()[2]);
    EXPECT_EQ(1.0, m_empty_beam.getIntensity());
    //EXPECT_EQ(size_t(4), m_empty_beam.parameterPool()->size());
//    EXPECT_EQ(1.0, m_empty_beam.parameterPool()->parameter(BornAgain::Intensity)->value());
//    EXPECT_EQ(1.0, m_empty_beam.parameterPool()->parameter(BornAgain::Wavelength)->value());
//    EXPECT_EQ(0.0, m_empty_beam.parameterPool()->parameter(BornAgain::Alpha)->value());
//    EXPECT_EQ(0.0, m_empty_beam.parameterPool()->parameter(BornAgain::Phi)->value());
//    EXPECT_EQ(complex_t(0.5, 0.0), m_empty_beam.getPolarization()(0, 0));
//    EXPECT_EQ(complex_t(0.5, 0.0), m_empty_beam.getPolarization()(1, 1));
}

TEST_F(BeamTest, BeamAssignment)
{
    kvector_t polarization(0.0, 0.0, 0.2);

    std::unique_ptr<Beam> P_beam{new Beam()};

    P_beam->setCentralK(1.0, 1.0, 1.0);
    P_beam->setIntensity(2.0);
    P_beam->setPolarization(polarization);

    Beam beam_copy = *P_beam;
    EXPECT_NEAR(1.83423, beam_copy.getCentralK()[0], 0.00001);
    EXPECT_NEAR(-2.85664, beam_copy.getCentralK()[1], 0.00001);
    EXPECT_NEAR(-5.28712, beam_copy.getCentralK()[2], 0.00001);
    EXPECT_EQ(double(2.0), beam_copy.getIntensity());
    /* TEMPORARILY DISABLED getParameterPool()
    EXPECT_EQ(size_t(4), beam_copy.getParameterPool()->size());
    EXPECT_EQ(double(2.0),
              beam_copy.getParameterPool()->getParameter(BornAgain::Intensity).getValue());
    EXPECT_EQ(complex_t(0.6, 0.0), beam_copy.getPolarization()(0, 0));
    EXPECT_EQ(complex_t(0.4, 0.0), beam_copy.getPolarization()(1, 1));
    */
}

TEST_F(BeamTest, BeamPolarization)
{
    Beam beam;
    kvector_t polarization(0.1, -0.2, 0.4);
    beam.setPolarization(polarization);

    kvector_t bloch_vector = beam.getBlochVector();
    EXPECT_NEAR(0.1, bloch_vector.x(), 1e-8);
    EXPECT_NEAR(-0.2, bloch_vector.y(), 1e-8);
    EXPECT_NEAR(0.4, bloch_vector.z(), 1e-8);
}

TEST_F(BeamTest, FootprintBehaviour)
{
    Beam beam;
    EXPECT_EQ(0.0, beam.footprintFactor().widthRatio());
    EXPECT_THROW(beam.setFootprintFactor(nullptr), std::runtime_error);

    beam.setWidthRatio(1.0);
    EXPECT_EQ(1.0, beam.footprintFactor().widthRatio());

    std::unique_ptr<FootprintFactorSquare> square_ff = std::make_unique<FootprintFactorSquare>(0.0);
    beam.setFootprintFactor(square_ff.get());

    Beam beam2 = beam;
    EXPECT_EQ(typeid(beam.footprintFactor()).hash_code(),
              typeid(beam2.footprintFactor()).hash_code());
    EXPECT_EQ(beam.footprintFactor().widthRatio(), beam2.footprintFactor().widthRatio());
    EXPECT_EQ(beam.footprintFactor().parent(), static_cast<INode*>(&beam));
    EXPECT_EQ(beam2.footprintFactor().parent(), static_cast<INode*>(&beam2));

    Beam beam3;
    beam = beam3;

    EXPECT_EQ(typeid(beam.footprintFactor()).hash_code(),
              typeid(beam3.footprintFactor()).hash_code());
    EXPECT_EQ(beam.footprintFactor().widthRatio(), beam3.footprintFactor().widthRatio());
    EXPECT_EQ(beam.footprintFactor().parent(), static_cast<INode*>(&beam));
    EXPECT_EQ(beam3.footprintFactor().parent(), static_cast<INode*>(&beam3));
}
