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

#include "IDistribution2DSampler.h"
#include <random>

IDistribution2DSampler::~IDistribution2DSampler() = default;

std::pair<double, double> Distribution2DCauchySampler::randomSample() const
{
    std::random_device rd;  // random device class instance
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<double> uniformDist(0.0, 1.0);

    double cdf_value_phi = uniformDist(gen);

    // solve for phi from the cdf of radial marginalzed distribution using Newton-Raphson method
    double func = 0.0, funcDeriv = 0.0, phi = 0.0;

    // initial guess for phi
    phi = 0.25;

    bool convergedSoln = false;
    while (!convergedSoln) {
        func = (phi + 1)*std::exp(-phi) + cdf_value_phi - 1;
        funcDeriv = std::exp(-phi) - (phi+1)*std::exp(-phi);

        phi = phi - func / funcDeriv;

        if (std::abs(func / funcDeriv) < 0.001)
            convergedSoln = true;
    }

    double alpha = uniformDist(gen);

    return std::make_pair(m_omega_x*phi*std::cos(M_2_PI*alpha),
                          m_omega_y*phi*std::sin(M_2_PI*alpha));
}

std::pair<double, double> Distribution2DGaussSampler::randomSample() const
{
    std::random_device rd;  // random device class instance
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<double> uniformDist(0.0, 1.0);

    double cdf_value_phi = uniformDist(gen);

    // solve for phi from the cdf of radial marginalzed distribution
    double phi = std::sqrt(-2*std::log(1-cdf_value_phi));

    double alpha = uniformDist(gen);

    return std::make_pair(m_omega_x*phi*std::cos(M_2_PI*alpha),
                          m_omega_y*phi*std::sin(M_2_PI*alpha));
}
