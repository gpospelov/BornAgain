// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/FTDistributions.cpp
//! @brief     Implements class FTDistribution2DCauchy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FTDistributions.h"
#include "BornAgainNamespace.h"
#include "MathFunctions.h"
#include "MemberFunctionIntegrator.h"

using namespace BornAgain;

//===============1D======================

void IFTDistribution1D::init_parameters()
{
    clearParameterPool();
    registerParameter(Omega, &m_omega);
}


FTDistribution1DCauchy::FTDistribution1DCauchy(double omega)
: IFTDistribution1D(omega)
{
    setName(FTDistribution1DCauchyType);
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
    return 1.0/(1.0 + sum_sq);
}

FTDistribution1DGauss::FTDistribution1DGauss(double omega)
: IFTDistribution1D(omega)
{
    setName(FTDistribution1DGaussType);
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
    return std::exp(-sum_sq/2.0);
}

FTDistribution1DGate::FTDistribution1DGate(double omega)
    : IFTDistribution1D(omega)
{
    setName(FTDistribution1DGateType);
    init_parameters();
}

FTDistribution1DGate *FTDistribution1DGate::clone() const
{
    FTDistribution1DGate *p_clone = new FTDistribution1DGate(m_omega);
    return p_clone;
}

double FTDistribution1DGate::evaluate(double q) const
{
    return MathFunctions::sinc(q*m_omega);
}

FTDistribution1DTriangle::FTDistribution1DTriangle(double omega)
    : IFTDistribution1D(omega)
{
    setName(FTDistribution1DTriangleType);
    init_parameters();
}

FTDistribution1DTriangle *FTDistribution1DTriangle::clone() const
{
    FTDistribution1DTriangle *p_clone = new FTDistribution1DTriangle(m_omega);
    return p_clone;
}

double FTDistribution1DTriangle::evaluate(double q) const
{
    double sincqw2 = MathFunctions::sinc(q*m_omega/2.0);
    return sincqw2*sincqw2;
}

FTDistribution1DCosine::FTDistribution1DCosine(double omega)
    : IFTDistribution1D(omega)
{
    setName(FTDistribution1DCosineType);
    init_parameters();
}

FTDistribution1DCosine *FTDistribution1DCosine::clone() const
{
    FTDistribution1DCosine *p_clone = new FTDistribution1DCosine(m_omega);
    return p_clone;
}

double FTDistribution1DCosine::evaluate(double q) const
{
    double qw = std::abs(q*m_omega);
    if (std::abs(qw/Units::PI-1.0) < Numeric::double_epsilon) {
        return 0.5;
    }
    else {
        return MathFunctions::sinc(qw)/(1.0-qw*qw/Units::PI/Units::PI);
    }
}

FTDistribution1DVoigt::FTDistribution1DVoigt(double omega, double eta)
: IFTDistribution1D(omega)
, m_eta(eta)
{
    setName(FTDistribution1DVoigtType);
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
    return m_eta*std::exp(-sum_sq/2.0)
            + (1.0 - m_eta)*1.0/(1.0 + sum_sq);
}

void FTDistribution1DVoigt::init_parameters()
{
    IFTDistribution1D::init_parameters();
    registerParameter(Eta, &m_eta);
}

void IFTDistribution1D::print(std::ostream& ostr) const
{
    ostr << getName() << " " << *getParameterPool();
}

//==============2D====================

double IFTDistribution2D::evaluateLattice(double, double) const
{
    throw NotImplementedException("IFTDistribution2D::evaluateLattice: This "
         "distribution can not be used for the reciprocal lattice approach");
}

void IFTDistribution2D::transformToStarBasis(double qX, double qY,
        double alpha, double a, double b, double& qa, double& qb) const
{
    double prefactor = 1.0/Units::PI2; // divide by sin(m_delta)
                                     // for unnormalized X*,Y* basis
    qa = a*prefactor*( std::sin(m_gamma+m_delta)*qX - std::sin(m_gamma)*qY );
    qb = b*prefactor*( -std::sin(alpha-m_gamma-m_delta)*qX + std::sin(alpha-m_gamma)*qY );
}

void IFTDistribution2D::init_parameters()
{
    clearParameterPool();
    registerParameter(CoherenceLengthX, &m_coherence_length_x);
    registerParameter(CoherenceLengthY, &m_coherence_length_y);
}

void IFTDistribution2D::print(std::ostream& ostr) const
{
    ostr << getName() << " " << *getParameterPool();
}


FTDistribution2DCauchy::FTDistribution2DCauchy(double coherence_length_x,
        double coherence_length_y)
: IFTDistribution2D(coherence_length_x, coherence_length_y)
{
    setName(FTDistribution2DCauchyType);
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

double FTDistribution2DCauchy::evaluateLattice(double qx, double qy) const
{
    return evaluate(qx, qy);
}

FTDistribution2DGauss::FTDistribution2DGauss(double coherence_length_x,
        double coherence_length_y)
: IFTDistribution2D(coherence_length_x, coherence_length_y)
{
    setName(FTDistribution2DGaussType);
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

double FTDistribution2DGauss::evaluateLattice(double qx, double qy) const
{
    double sum_sq = qx*qx*m_coherence_length_x*m_coherence_length_x
            + qy*qy*m_coherence_length_y*m_coherence_length_y;
    return std::exp(-sum_sq/4.0)/2.0;
}

FTDistribution2DGate::FTDistribution2DGate(double coherence_length_x,
        double coherence_length_y)
: IFTDistribution2D(coherence_length_x, coherence_length_y)
{
    setName(FTDistribution2DGateType);
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
    return MathFunctions::Bessel_C1(scaled_q)*2.0;
}

FTDistribution2DCone::FTDistribution2DCone(double coherence_length_x,
        double coherence_length_y)
: IFTDistribution2D(coherence_length_x, coherence_length_y)
{
    setName(FTDistribution2DConeType);
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
    if (scaled_q<Numeric::double_epsilon) {
        return 1.0 - 3.0*scaled_q*scaled_q/40.0;
    }
    MemberFunctionIntegrator<FTDistribution2DCone>::mem_function
        p_member_function = &FTDistribution2DCone::coneIntegrand2;
    MemberFunctionIntegrator<FTDistribution2DCone>
                integrator(p_member_function, this);
    double integral = integrator.integrate(0.0, scaled_q, (void*)0);
    return 6.0*(MathFunctions::Bessel_C1(scaled_q)
                - integral/scaled_q/scaled_q/scaled_q);
}

double FTDistribution2DCone::coneIntegrand2(double value, void *params) const
{
    (void)params;
    return value*value*MathFunctions::Bessel_J0(value);
}

FTDistribution2DVoigt::FTDistribution2DVoigt(double coherence_length_x,
        double coherence_length_y, double eta)
: IFTDistribution2D(coherence_length_x, coherence_length_y)
, m_eta(eta)
{
    setName(FTDistribution2DVoigtType);
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

double FTDistribution2DVoigt::evaluateLattice(double qx, double qy) const
{
    double sum_sq = qx*qx*m_coherence_length_x*m_coherence_length_x
            + qy*qy*m_coherence_length_y*m_coherence_length_y;
    return m_eta*std::exp(-sum_sq/4.0)/2.0
           + (1.0 - m_eta)*std::pow(1.0 + sum_sq, -1.5);
}

void FTDistribution2DVoigt::init_parameters()
{
    IFTDistribution2D::init_parameters();
    registerParameter(Eta, &m_eta);
}
