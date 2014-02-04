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
#include "MemberFunctionIntegrator.h"


//===============1D======================

void IFTDistribution1D::init_parameters()
{
    clearParameterPool();
    registerParameter("omega", &m_omega);
}


FTDistribution1DCauchy::FTDistribution1DCauchy(double omega)
: IFTDistribution1D(omega)
{
    setName("1DDistributionCauchy");
    init_parameters();
}

FTDistribution1DCauchy* FTDistribution1DCauchy::clone() const
{
    FTDistribution1DCauchy *p_clone = new FTDistribution1DCauchy(m_omega);
    return p_clone;
}

double FTDistribution1DCauchy::evaluate(double q) const
{
    double sum_sq = q*q*m_omega*m_omega;
    return std::pow(1.0 + sum_sq, -1.5);
}

FTDistribution1DGauss::FTDistribution1DGauss(double omega)
: IFTDistribution1D(omega)
{
    setName("1DDistributionGauss");
    init_parameters();
}

FTDistribution1DGauss* FTDistribution1DGauss::clone() const
{
    FTDistribution1DGauss *p_clone = new FTDistribution1DGauss(m_omega);
    return p_clone;
}

double FTDistribution1DGauss::evaluate(double q) const
{
    double sum_sq = q*q*m_omega*m_omega;
    return std::exp(-sum_sq/4.0)/2.0;
}

FTDistribution1DVoigt::FTDistribution1DVoigt(double omega, double eta)
: IFTDistribution1D(omega)
, m_eta(eta)
{
    setName("1DDistributionVoigt");
    init_parameters();
}

FTDistribution1DVoigt* FTDistribution1DVoigt::clone() const
{
    FTDistribution1DVoigt *p_clone = new FTDistribution1DVoigt(
            m_omega, m_eta);
    return p_clone;
}

double FTDistribution1DVoigt::evaluate(double q) const
{
    double sum_sq = q*q*m_omega*m_omega;
    return m_eta*std::exp(-sum_sq/4.0)/2.0
            + (1.0 - m_eta)*std::pow(1.0 + sum_sq, -1.5);
}

void FTDistribution1DVoigt::init_parameters()
{
    IFTDistribution1D::init_parameters();
    registerParameter("eta", &m_eta);
}

//==============2D====================

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

