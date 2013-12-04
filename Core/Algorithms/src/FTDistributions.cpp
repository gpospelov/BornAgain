// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/FTDistributions.cpp
//! @brief     Implements class FTDistribution2DCauchy.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FTDistributions.h"
#include "MathFunctions.h"

void IFTDistribution2D::transformToStarBasis(double qX, double qY,
        double alpha, double a, double b, double& qa, double& qb) const
{
    double prefactor = 1.0/(2*M_PI); // divide by sin(m_delta)
                                     // for unnormalized X*,Y* basis
    qa = a*prefactor*( std::sin(m_gamma+m_delta)*qX - std::sin(m_gamma)*qY );
    qb = b*prefactor*( -std::sin(alpha-m_gamma-m_delta)*qX + std::sin(alpha-m_gamma)*qY );
}

void IFTDistribution2D::init_parameters()
{
    clearParameterPool();
    registerParameter("coherence_length_x", &m_coherence_length_x);
    registerParameter("coherence_length_y", &m_coherence_length_y);
}

FTDistribution2DCauchy::FTDistribution2DCauchy(double coherence_length_x,
        double coherence_length_y)
: IFTDistribution2D(coherence_length_x, coherence_length_y)
{
    setName("2DDistributionCauchy");
    init_parameters();
}

FTDistribution2DCauchy* FTDistribution2DCauchy::clone() const
{
    FTDistribution2DCauchy *p_clone = new FTDistribution2DCauchy(
            m_coherence_length_x, m_coherence_length_y);
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
    setName("2DDistributionGauss");
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
    return std::exp(-sum_sq/4.0)/2.0;
}

FTDistribution2DGate::FTDistribution2DGate(double coherence_length_x,
        double coherence_length_y)
: IFTDistribution2D(coherence_length_x, coherence_length_y)
{
    setName("2DDistributionGate");
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
    return MathFunctions::Bessel_C1(scaled_q);
}

FTDistribution2DVoigt::FTDistribution2DVoigt(double coherence_length_x,
        double coherence_length_y, double eta)
: IFTDistribution2D(coherence_length_x, coherence_length_y)
, m_eta(eta)
{
    setName("2DDistributionVoigt");
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
    return m_eta*std::exp(-sum_sq/4.0)/2.0
            + (1.0 - m_eta)*std::pow(1.0 + sum_sq, -1.5);
}

void FTDistribution2DVoigt::init_parameters()
{
    IFTDistribution2D::init_parameters();
    registerParameter("eta", &m_eta);
}

