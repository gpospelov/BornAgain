#ifndef INSTRUMENTTEST_H_
#define INSTRUMENTTEST_H_

#include "Instrument.h"

class InstrumentTest : public ::testing::Test
{
 protected:
    InstrumentTest();
    virtual ~InstrumentTest();

    Instrument m_instrument;
    OutputData<double> m_data;
};


InstrumentTest::InstrumentTest()
{
    m_data.addAxis("phi_f", 10, 0., 10.);
    m_data.addAxis("theta_f", 20, 0., 20.);
}

InstrumentTest::~InstrumentTest()
{
}

TEST_F(InstrumentTest, InstrumentInitialState)
{
    EXPECT_EQ( double(1), m_instrument.getBeam().getIntensity());
}


TEST_F(InstrumentTest, BeamManipulation)
{
    double lambda(1), alpha(-1), phi(1);
    double k = 2.*M_PI/lambda;
    double x = k*std::cos(alpha) * std::cos(phi);
    double y = k*std::cos(alpha) * std::sin(phi);
    double z = k*std::sin(alpha);
    m_instrument.setBeamParameters(lambda, alpha, phi);
    EXPECT_DOUBLE_EQ(x, m_instrument.getBeam().getCentralK().x().real() );
    EXPECT_DOUBLE_EQ(0, m_instrument.getBeam().getCentralK().x().imag() );
    EXPECT_DOUBLE_EQ(y, m_instrument.getBeam().getCentralK().y().real() );
    EXPECT_DOUBLE_EQ(0, m_instrument.getBeam().getCentralK().y().imag() );
    EXPECT_DOUBLE_EQ(z, m_instrument.getBeam().getCentralK().z().real() );
    EXPECT_DOUBLE_EQ(0, m_instrument.getBeam().getCentralK().z().imag() );

    EXPECT_FALSE( m_instrument.getDetectorDimension()==2 );
    m_instrument.matchDetectorParameters(m_data);
    EXPECT_TRUE( m_instrument.getDetectorDimension()==2 );
    //TODO: add axes check

    m_instrument.setBeamIntensity(10);
    EXPECT_EQ( double(10), m_instrument.getIntensity());
}

TEST_F(InstrumentTest, InstrumentClone)
{
    Instrument clone(m_instrument);
    EXPECT_EQ( size_t(0), clone.getDetectorDimension() );
    EXPECT_EQ( double(1), clone.getIntensity() );
}

#endif /* INSTRUMENTTEST_H_ */
