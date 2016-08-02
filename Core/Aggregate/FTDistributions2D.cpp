// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/FTDistributions2D.cpp
//! @brief     Implements interface class IFTDistribution2D and children thereof.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FTDistributions2D.h"
#include "BornAgainNamespace.h"
#include "IntegratorReal.h"
#include "MathFunctions.h"
#include "Numeric.h"
#include "ParameterPool.h"
#include "Units.h"

IFTDistribution2D::IFTDistribution2D(double coherence_length_x, double coherence_length_y)
    : m_coherence_length_x(coherence_length_x)
    , m_coherence_length_y(coherence_length_y)
    , m_gamma(0.0)
    , m_delta(Units::PI/2.0)
{}

void IFTDistribution2D::init_parameters()
{
    registerNonnegativeLength(BornAgain::CoherenceLengthX, &m_coherence_length_x);
    registerNonnegativeLength(BornAgain::CoherenceLengthY, &m_coherence_length_y);
}

void IFTDistribution2D::print(std::ostream& ostr) const
{
    ostr << getName() << " " << *getParameterPool();
}


FTDistribution2DCauchy::FTDistribution2DCauchy(double coherence_length_x,
        double coherence_length_y)
: IFTDistribution2D(coherence_length_x, coherence_length_y)
{
    setName(BornAgain::FTDistribution2DCauchyType);
    init_parameters();
}

FTDistribution2DCauchy *FTDistribution2DCauchy::clone() const
{
    FTDistribution2DCauchy *p_clone
        = new FTDistribution2DCauchy(m_coherence_length_x, m_coherence_length_y);
    p_clone->setGamma(m_gamma);
    return p_clone;
}

double FTDistribution2DCauchy::evaluate(double qx, double qy) const
{
    double sum_sq = qx*qx*m_coherence_length_x*m_coherence_length_x
            + qy*qy*m_coherence_length_y*m_coherence_length_y;
    return std::pow(1.0 + sum_sq, -1.5);
}


FTDistribution2DGauss::FTDistribution2DGauss(double coherence_length_x,
        double coherence_length_y)
: IFTDistribution2D(coherence_length_x, coherence_length_y)
{
    setName(BornAgain::FTDistribution2DGaussType);
    init_parameters();
}

FTDistribution2DGauss* FTDistribution2DGauss::clone() const
{
    FTDistribution2DGauss *p_clone = new FTDistribution2DGauss(
            m_coherence_length_x, m_coherence_length_y);
    p_clone->setGamma(m_gamma);
    return p_clone;
}

double FTDistribution2DGauss::evaluate(double qx, double qy) const
{
    double sum_sq = qx*qx*m_coherence_length_x*m_coherence_length_x
            + qy*qy*m_coherence_length_y*m_coherence_length_y;
    return std::exp(-sum_sq/2.0);
}


FTDistribution2DGate::FTDistribution2DGate(double coherence_length_x,
        double coherence_length_y)
: IFTDistribution2D(coherence_length_x, coherence_length_y)
{
    setName(BornAgain::FTDistribution2DGateType);
    init_parameters();
}

FTDistribution2DGate* FTDistribution2DGate::clone() const
{
    FTDistribution2DGate *p_clone = new FTDistribution2DGate(
            m_coherence_length_x, m_coherence_length_y);
    p_clone->setGamma(m_gamma);
    return p_clone;
}

double FTDistribution2DGate::evaluate(double qx, double qy) const
{
    double scaled_q = std::sqrt(qx*qx*m_coherence_length_x*m_coherence_length_x
            + qy*qy*m_coherence_length_y*m_coherence_length_y);
    return MathFunctions::Bessel_J1c(scaled_q)*2.0;
}


FTDistribution2DCone::FTDistribution2DCone(double coherence_length_x,
        double coherence_length_y)
    : IFTDistribution2D(coherence_length_x, coherence_length_y)
{
    setName(BornAgain::FTDistribution2DConeType);
    init_parameters();
}

FTDistribution2DCone* FTDistribution2DCone::clone() const
{
    FTDistribution2DCone *p_clone = new FTDistribution2DCone(
            m_coherence_length_x, m_coherence_length_y);
    p_clone->setGamma(m_gamma);
    return p_clone;
}

double FTDistribution2DCone::evaluate(double qx, double qy) const
{
    double scaled_q = std::sqrt(qx*qx*m_coherence_length_x*m_coherence_length_x
            + qy*qy*m_coherence_length_y*m_coherence_length_y);
    if (scaled_q<Numeric::double_epsilon)
        return 1.0 - 3.0*scaled_q*scaled_q/40.0;
    auto integrator = make_integrator_real(this, &FTDistribution2DCone::coneIntegrand2);
    double integral = integrator->integrate(0.0, scaled_q);
    return 6.0*(MathFunctions::Bessel_J1c(scaled_q)
                - integral/scaled_q/scaled_q/scaled_q);
}

double FTDistribution2DCone::coneIntegrand2(double value) const
{
    return value*value*MathFunctions::Bessel_J0(value);
}


FTDistribution2DVoigt::FTDistribution2DVoigt(double coherence_length_x,
        double coherence_length_y, double eta)
    : IFTDistribution2D(coherence_length_x, coherence_length_y), m_eta(eta)
{
    setName(BornAgain::FTDistribution2DVoigtType);
    init_parameters();
}

FTDistribution2DVoigt* FTDistribution2DVoigt::clone() const
{
    FTDistribution2DVoigt *p_clone = new FTDistribution2DVoigt(
            m_coherence_length_x, m_coherence_length_y, m_eta);
    p_clone->setGamma(m_gamma);
    return p_clone;
}

double FTDistribution2DVoigt::evaluate(double qx, double qy) const
{
    double sum_sq = qx*qx*m_coherence_length_x*m_coherence_length_x
            + qy*qy*m_coherence_length_y*m_coherence_length_y;
    return m_eta*std::exp(-sum_sq/2.0)
            + (1.0 - m_eta)*std::pow(1.0 + sum_sq, -1.5);
}

void FTDistribution2DVoigt::init_parameters()
{
    IFTDistribution2D::init_parameters();
    registerUnlimitedScalar(BornAgain::Eta, &m_eta);
}
