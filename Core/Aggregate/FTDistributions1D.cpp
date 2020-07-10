// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/FTDistributions1D.cpp
//! @brief     Implements interface class IFTDistribution2D and children thereof.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Aggregate/FTDistributions1D.h"
#include "Core/Basics/Exceptions.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Parametrization/ParameterPool.h"
#include "Core/Parametrization/RealParameter.h"
#include "Core/Tools/MathFunctions.h"
#include <limits>

namespace
{
const double CosineDistributionFactor = 1.0 / 3.0 - 2.0 / M_PI / M_PI;
}

IFTDistribution1D::~IFTDistribution1D() = default;

void IFTDistribution1D::init_parameters()
{
    registerParameter("Omega", &m_omega);
}

FTDistribution1DCauchy::FTDistribution1DCauchy(double omega) : IFTDistribution1D(omega)
{
    setName("FTDistribution1DCauchy");
    init_parameters();
}

FTDistribution1DCauchy* FTDistribution1DCauchy::clone() const
{
    return new FTDistribution1DCauchy(m_omega);
}

double FTDistribution1DCauchy::evaluate(double q) const
{
    double sum_sq = q * q * m_omega * m_omega;
    return 1.0 / (1.0 + sum_sq);
}

double FTDistribution1DCauchy::qSecondDerivative() const
{
    return 2.0 * m_omega * m_omega;
}

std::unique_ptr<IDistribution1DSampler> FTDistribution1DCauchy::createSampler() const
{
    return std::make_unique<Distribution1DCauchySampler>(1 / m_omega);
}

FTDistribution1DGauss::FTDistribution1DGauss(double omega) : IFTDistribution1D(omega)
{
    setName("FTDistribution1DGauss");
    init_parameters();
}

FTDistribution1DGauss* FTDistribution1DGauss::clone() const
{
    return new FTDistribution1DGauss(m_omega);
}

double FTDistribution1DGauss::evaluate(double q) const
{
    double sum_sq = q * q * m_omega * m_omega;
    return std::exp(-sum_sq / 2.0);
}

double FTDistribution1DGauss::qSecondDerivative() const
{
    return m_omega * m_omega;
}

std::unique_ptr<IDistribution1DSampler> FTDistribution1DGauss::createSampler() const
{
    return std::make_unique<Distribution1DGaussSampler>(0.0, m_omega);
}

FTDistribution1DGate::FTDistribution1DGate(double omega) : IFTDistribution1D(omega)
{
    setName("FTDistribution1DGate");
    init_parameters();
}

FTDistribution1DGate* FTDistribution1DGate::clone() const
{
    return new FTDistribution1DGate(m_omega);
}

double FTDistribution1DGate::evaluate(double q) const
{
    return MathFunctions::sinc(q * m_omega);
}

double FTDistribution1DGate::qSecondDerivative() const
{
    return m_omega * m_omega / 3.0;
}

std::unique_ptr<IDistribution1DSampler> FTDistribution1DGate::createSampler() const
{
    return std::make_unique<Distribution1DGateSampler>(-m_omega, m_omega);
}

FTDistribution1DTriangle::FTDistribution1DTriangle(double omega) : IFTDistribution1D(omega)
{
    setName("FTDistribution1DTriangle");
    init_parameters();
}

FTDistribution1DTriangle* FTDistribution1DTriangle::clone() const
{
    return new FTDistribution1DTriangle(m_omega);
}

double FTDistribution1DTriangle::evaluate(double q) const
{
    double sincqw2 = MathFunctions::sinc(q * m_omega / 2.0);
    return sincqw2 * sincqw2;
}

double FTDistribution1DTriangle::qSecondDerivative() const
{
    return m_omega * m_omega / 6.0;
}

std::unique_ptr<IDistribution1DSampler> FTDistribution1DTriangle::createSampler() const
{
    return std::make_unique<Distribution1DTriangleSampler>(m_omega);
}

FTDistribution1DCosine::FTDistribution1DCosine(double omega) : IFTDistribution1D(omega)
{
    setName("FTDistribution1DCosine");
    init_parameters();
}

FTDistribution1DCosine* FTDistribution1DCosine::clone() const
{
    return new FTDistribution1DCosine(m_omega);
}

double FTDistribution1DCosine::evaluate(double q) const
{
    double qw = std::abs(q * m_omega);
    if (std::abs(1.0 - qw * qw / M_PI / M_PI) < std::numeric_limits<double>::epsilon())
        return 0.5;
    return MathFunctions::sinc(qw) / (1.0 - qw * qw / M_PI / M_PI);
}

double FTDistribution1DCosine::qSecondDerivative() const
{
    return CosineDistributionFactor * m_omega * m_omega;
}

std::unique_ptr<IDistribution1DSampler> FTDistribution1DCosine::createSampler() const
{
    return std::make_unique<Distribution1DCosineSampler>(m_omega);
}

FTDistribution1DVoigt::FTDistribution1DVoigt(double omega, double eta)
    : IFTDistribution1D(omega), m_eta(eta)
{
    setName("FTDistribution1DVoigt");
    init_parameters();
    registerParameter("Eta", &m_eta);
}

FTDistribution1DVoigt* FTDistribution1DVoigt::clone() const
{
    return new FTDistribution1DVoigt(m_omega, m_eta);
}

double FTDistribution1DVoigt::evaluate(double q) const
{
    double sum_sq = q * q * m_omega * m_omega;
    return m_eta * std::exp(-sum_sq / 2.0) + (1.0 - m_eta) * 1.0 / (1.0 + sum_sq);
}

double FTDistribution1DVoigt::qSecondDerivative() const
{
    return (2.0 - m_eta) * m_omega * m_omega;
}

std::unique_ptr<IDistribution1DSampler> FTDistribution1DVoigt::createSampler() const
{
    // TODO Need to implement 1D Voigt

    std::ostringstream ostr;
    ostr << "FTDistribution1DVoigt::createSampler() -> Error in class initialization";
    ostr << "\n\n Has not been implemented yet...stay tuned!";
    throw Exceptions::ClassInitializationException(ostr.str());
}
