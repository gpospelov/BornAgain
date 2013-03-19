// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/StochasticGaussian.cpp
//! @brief     Implements class StochasticGaussian.
//!
//! @homepage  apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#include "StochasticGaussian.h"
#include "MathFunctions.h"

StochasticDoubleGaussian::StochasticDoubleGaussian(double average, double std_dev)
    : StochasticParameter<double>(average)
    , m_std_dev(std_dev)
{
}

StochasticDoubleGaussian::~StochasticDoubleGaussian()
{
}

void StochasticDoubleGaussian::setToRandom()
{
    m_current = MathFunctions::GenerateNormalRandom(m_average, m_std_dev);
}

StochasticDoubleGaussian* StochasticDoubleGaussian::clone() const
{
    StochasticDoubleGaussian *p_new = new StochasticDoubleGaussian(m_average, m_std_dev);
    p_new->m_current = m_current;
    return p_new;
}

double StochasticDoubleGaussian::probabilityDensity(double value) const
{
    return MathFunctions::Gaussian(value, m_average, m_std_dev);
}
