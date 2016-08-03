// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/FTDistributions1D.cpp
//! @brief     Implements interface class IFTDistribution2D and children thereof.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FTDistributions1D.h"
#include "BornAgainNamespace.h"
#include "IntegratorReal.h"
#include "MathFunctions.h"
#include "Numeric.h"
#include "ParameterPool.h"
#include "Units.h"

void IFTDistribution1D::print(std::ostream& ostr) const
{
    ostr << getName() << " " << *getParameterPool();
}

void IFTDistribution1D::init_parameters()
{
    registerUnlimitedScalar(BornAgain::Omega, &m_omega);
}


FTDistribution1DCauchy::FTDistribution1DCauchy(double omega)
: IFTDistribution1D(omega)
{
    setName(BornAgain::FTDistribution1DCauchyType);
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
    setName(BornAgain::FTDistribution1DGaussType);
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
    setName(BornAgain::FTDistribution1DGateType);
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
    setName(BornAgain::FTDistribution1DTriangleType);
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
    setName(BornAgain::FTDistribution1DCosineType);
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
    setName(BornAgain::FTDistribution1DVoigtType);
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
    registerUnlimitedScalar(BornAgain::Eta, &m_eta);
}
