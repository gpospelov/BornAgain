// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/FTDecay1D.cpp
//! @brief     Implements class FTDistribution2DCauchy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Aggregate/FTDecay1D.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Parametrization/ParameterPool.h"
#include "Core/Parametrization/RealParameter.h"
#include "Core/Tools/MathFunctions.h"
#include <algorithm>

IFTDecayFunction1D::IFTDecayFunction1D(double decay_length) : m_decay_length(decay_length) {}

void IFTDecayFunction1D::register_decay_length()
{
    registerParameter("DecayLength", &m_decay_length);
}

FTDecayFunction1DCauchy::FTDecayFunction1DCauchy(double decay_length)
    : IFTDecayFunction1D(decay_length)
{
    setName("FTDecayFunction1DCauchy");
    register_decay_length();
}

FTDecayFunction1DCauchy* FTDecayFunction1DCauchy::clone() const
{
    return new FTDecayFunction1DCauchy(m_decay_length);
}

double FTDecayFunction1DCauchy::evaluate(double q) const
{
    double sum_sq = q * q * m_decay_length * m_decay_length;
    return m_decay_length * 2.0 / (1.0 + sum_sq);
}

FTDecayFunction1DGauss::FTDecayFunction1DGauss(double decay_length)
    : IFTDecayFunction1D(decay_length)
{
    setName("FTDecayFunction1DGauss");
    register_decay_length();
}

FTDecayFunction1DGauss* FTDecayFunction1DGauss::clone() const
{
    return new FTDecayFunction1DGauss(m_decay_length);
}

double FTDecayFunction1DGauss::evaluate(double q) const
{
    double sum_sq = q * q * m_decay_length * m_decay_length;
    return m_decay_length * std::sqrt(M_TWOPI) * std::exp(-sum_sq / 2.0);
}

FTDecayFunction1DTriangle::FTDecayFunction1DTriangle(double decay_length)
    : IFTDecayFunction1D(decay_length)
{
    setName("FTDecayFunction1DTriangle");
    register_decay_length();
}

FTDecayFunction1DTriangle* FTDecayFunction1DTriangle::clone() const
{
    return new FTDecayFunction1DTriangle(m_decay_length);
}

double FTDecayFunction1DTriangle::evaluate(double q) const
{
    double sincqw2 = MathFunctions::sinc(q * m_decay_length / 2.0);
    return m_decay_length * sincqw2 * sincqw2;
}

FTDecayFunction1DVoigt::FTDecayFunction1DVoigt(double decay_length, double eta)
    : IFTDecayFunction1D(decay_length), m_eta(eta)
{
    setName("FTDecayFunction1DVoigt");
    register_decay_length();
    registerParameter("Eta", &m_eta);
}

FTDecayFunction1DVoigt* FTDecayFunction1DVoigt::clone() const
{
    return new FTDecayFunction1DVoigt(m_decay_length, m_eta);
}

double FTDecayFunction1DVoigt::evaluate(double q) const
{
    double sum_sq = q * q * m_decay_length * m_decay_length;
    return m_eta * m_decay_length * std::sqrt(M_TWOPI) * std::exp(-sum_sq / 2.0)
           + (1.0 - m_eta) * m_decay_length * 2.0 / (1.0 + sum_sq);
}
