// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Assembly/FTDecayFunctions.cpp
//! @brief     Implements class FTDistribution2DCauchy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "BornAgainNamespace.h"
#include "MathFunctions.h"
#include "FTDecayFunctions.h"

using namespace BornAgain;

//===============1D======================


void IFTDecayFunction1D::print(std::ostream &ostr) const
{
    ostr << getName() << " " << *getParameterPool();
}

void IFTDecayFunction1D::init_parameters()
{
    clearParameterPool();
    registerParameter(Omega, &m_omega);
}

FTDecayFunction1DCauchy::FTDecayFunction1DCauchy(double omega)
: IFTDecayFunction1D(omega)
{
    setName(FTDecayFunction1DCauchyType);
    init_parameters();
}

FTDecayFunction1DCauchy* FTDecayFunction1DCauchy::clone() const
{
    FTDecayFunction1DCauchy *p_clone = new FTDecayFunction1DCauchy(m_omega);
    return p_clone;
}

double FTDecayFunction1DCauchy::evaluate(double q) const
{
    double sum_sq = q*q*m_omega*m_omega;
    return m_omega*2.0/(1.0 + sum_sq);
}

FTDecayFunction1DGauss::FTDecayFunction1DGauss(double omega)
: IFTDecayFunction1D(omega)
{
    setName(FTDecayFunction1DGaussType);
    init_parameters();
}

FTDecayFunction1DGauss* FTDecayFunction1DGauss::clone() const
{
    FTDecayFunction1DGauss *p_clone = new FTDecayFunction1DGauss(m_omega);
    return p_clone;
}

double FTDecayFunction1DGauss::evaluate(double q) const
{
    double sum_sq = q*q*m_omega*m_omega;
    return m_omega*std::sqrt(Units::PI2)*std::exp(-sum_sq/2.0);
}

FTDecayFunction1DTriangle::FTDecayFunction1DTriangle(double omega)
    : IFTDecayFunction1D(omega)
{
    setName(FTDecayFunction1DTriangleType);
    init_parameters();
}

FTDecayFunction1DTriangle *FTDecayFunction1DTriangle::clone() const
{
    FTDecayFunction1DTriangle *p_clone = new FTDecayFunction1DTriangle(m_omega);
    return p_clone;
}

double FTDecayFunction1DTriangle::evaluate(double q) const
{
    double sincqw2 = MathFunctions::sinc(q*m_omega/2.0);
    return m_omega*sincqw2*sincqw2;
}

FTDecayFunction1DVoigt::FTDecayFunction1DVoigt(double omega, double eta)
: IFTDecayFunction1D(omega)
, m_eta(eta)
{
    setName(FTDecayFunction1DVoigtType);
    init_parameters();
}

FTDecayFunction1DVoigt* FTDecayFunction1DVoigt::clone() const
{
    FTDecayFunction1DVoigt *p_clone = new FTDecayFunction1DVoigt(
            m_omega, m_eta);
    return p_clone;
}

double FTDecayFunction1DVoigt::evaluate(double q) const
{
    double sum_sq = q*q*m_omega*m_omega;
    return m_eta*m_omega*std::sqrt(Units::PI2)*std::exp(-sum_sq/2.0)
            + (1.0 - m_eta)*m_omega*2.0/(1.0 + sum_sq);
}

void FTDecayFunction1DVoigt::init_parameters()
{
    IFTDecayFunction1D::init_parameters();
    registerParameter(Eta, &m_eta);
}

/* Commented out decay functions: see header for rationale
FTDecayFunction1DGate::FTDecayFunction1DGate(double omega)
    : IFTDecayFunction1D(omega)
{
    setName(FTDecayFunction1DGateType);
    init_parameters();
}

FTDecayFunction1DGate *FTDecayFunction1DGate::clone() const
{
    FTDecayFunction1DGate *p_clone = new FTDecayFunction1DGate(m_omega);
    return p_clone;
}

double FTDecayFunction1DGate::evaluate(double q) const
{
    return 2.0*m_omega*MathFunctions::Sinc(q*m_omega);
}

FTDecayFunction1DCosine::FTDecayFunction1DCosine(double omega)
    : IFTDecayFunction1D(omega)
{
    setName(FTDecayFunction1DCosineType);
    init_parameters();
}

FTDecayFunction1DCosine *FTDecayFunction1DCosine::clone() const
{
    FTDecayFunction1DCosine *p_clone = new FTDecayFunction1DCosine(m_omega);
    return p_clone;
}

double FTDecayFunction1DCosine::evaluate(double q) const
{
    double qw = std::abs(q*m_omega);
    if (std::abs(qw/Units::PI-1.0) < Numeric::double_epsilon) {
        return m_omega/2.0;
    }
    else {
        return m_omega*MathFunctions::Sinc(qw)/(1.0-qw*qw/Units::PI/Units::PI);
    }
}
*/

//==============2D====================

void IFTDecayFunction2D::transformToStarBasis(double qX, double qY, double alpha,
                                              double a, double b, double &qa, double &qb) const
{
    double prefactor = 1.0/Units::PI2; // divide by sin(m_delta)
                                     // for unnormalized X*,Y* basis
    qa = a*prefactor*( std::sin(m_gamma+m_delta)*qX - std::sin(m_gamma)*qY );
    qb = b*prefactor*( -std::sin(alpha-m_gamma-m_delta)*qX + std::sin(alpha-m_gamma)*qY );
}

void IFTDecayFunction2D::print(std::ostream &ostr) const
{
    ostr << getName() << " " << *getParameterPool();
}

void IFTDecayFunction2D::init_parameters()
{
    clearParameterPool();
    registerParameter(OmegaX, &m_omega_x);
    registerParameter(OmegaY, &m_omega_y);
}

FTDecayFunction2DCauchy::FTDecayFunction2DCauchy(double decay_length_x, double decay_length_y)
    : IFTDecayFunction2D(decay_length_x, decay_length_y)
{
    setName(FTDecayFunction2DCauchyType);
    init_parameters();
}

FTDecayFunction2DCauchy *FTDecayFunction2DCauchy::clone() const
{
    FTDecayFunction2DCauchy *p_clone = new FTDecayFunction2DCauchy(m_omega_x, m_omega_y);
    p_clone->setGamma(m_gamma);
    return p_clone;
}

double FTDecayFunction2DCauchy::evaluate(double qx, double qy) const
{
    double sum_sq = qx*qx*m_omega_x*m_omega_x + qy*qy*m_omega_y*m_omega_y;
    return Units::PI2*m_omega_x*m_omega_y*std::pow(1.0 + sum_sq, -1.5);
}

FTDecayFunction2DGauss::FTDecayFunction2DGauss(double decay_length_x, double decay_length_y)
    : IFTDecayFunction2D(decay_length_x, decay_length_y)
{
    setName(FTDecayFunction2DGaussType);
    init_parameters();
}

FTDecayFunction2DGauss *FTDecayFunction2DGauss::clone() const
{
    FTDecayFunction2DGauss *p_clone = new FTDecayFunction2DGauss(m_omega_x, m_omega_y);
    p_clone->setGamma(m_gamma);
    return p_clone;
}

double FTDecayFunction2DGauss::evaluate(double qx, double qy) const
{
    double sum_sq = qx*qx*m_omega_x*m_omega_x + qy*qy*m_omega_y*m_omega_y;
    return Units::PI2*m_omega_x*m_omega_y*std::exp(-sum_sq/2.0);
}

FTDecayFunction2DVoigt::FTDecayFunction2DVoigt(double decay_length_x, double decay_length_y,
                                               double eta)
    : IFTDecayFunction2D(decay_length_x, decay_length_y)
    , m_eta(eta)
{
    setName(FTDecayFunction2DVoigtType);
    init_parameters();
}

FTDecayFunction2DVoigt *FTDecayFunction2DVoigt::clone() const
{
    FTDecayFunction2DVoigt *p_clone = new FTDecayFunction2DVoigt(m_omega_x, m_omega_y, m_eta);
    p_clone->setGamma(m_gamma);
    return p_clone;
}

double FTDecayFunction2DVoigt::evaluate(double qx, double qy) const
{
    double sum_sq = qx*qx*m_omega_x*m_omega_x + qy*qy*m_omega_y*m_omega_y;
    return Units::PI2*m_omega_x*m_omega_y*(m_eta*std::exp(-sum_sq/2.0)
                                           + (1.0-m_eta)*std::pow(1.0 + sum_sq, -1.5));
}

void FTDecayFunction2DVoigt::init_parameters()
{
    IFTDecayFunction2D::init_parameters();
    registerParameter(Eta, &m_eta);
}
