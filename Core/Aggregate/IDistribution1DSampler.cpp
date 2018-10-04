// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/FTDistributions1D.h
//! @brief     Defines interface class IFTDistribution1D, and children thereof
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "IDistribution1DSampler.h"
#include <random>

IDistribution1DSampler::~IDistribution1DSampler() =default;

double Distribution1DGaussSampler::randomSample() const
{
    std::random_device rd; // random device class instance
    std::mt19937 gen(rd());
    std::normal_distribution<double> normalDist(m_mean, m_stddev);

    return normalDist(gen);
}
