// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/FTDecay2D.cpp
//! @brief     Implements class FTDistribution2DCauchy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Aggregate/FTDecay2D.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Parametrization/ParameterPool.h"
#include "Core/Parametrization/RealParameter.h"
#include "Core/Tools/MathFunctions.h"
#include <algorithm>

//! Constructor of two-dimensional decay function in reciprocal space.
//! @param decay_length_x: the decay length in nanometers along x-axis of the distribution
//! @param decay_length_y: the decay length in nanometers along y-axis of the distribution
//! @param gamma: distribution orientation with respect to the corresponding lattice vector
//! in radians
IFTDecayFunction2D::IFTDecayFunction2D(double decay_length_x, double decay_length_y, double gamma)
    : m_decay_length_x(decay_length_x), m_decay_length_y(decay_length_y), m_gamma(gamma)
{
    registerParameter("DecayLengthX", &m_decay_length_x).setUnit("nm").setNonnegative();
    registerParameter("DecayLengthY", &m_decay_length_y).setUnit("nm").setNonnegative();
    registerParameter("Gamma", &m_gamma).setUnit("rad").setLimited(-M_PI_2, M_PI_2);
}

//! Calculates bounding values of reciprocal lattice coordinates that contain the centered
//! rectangle with a corner defined by qX and qY
std::pair<double, double>
IFTDecayFunction2D::boundingReciprocalLatticeCoordinates(double qX, double qY, double a, double b,
                                                         double alpha) const
{
    auto q_bounds_1 = transformToRecLatticeCoordinates(qX, qY, a, b, alpha);
    auto q_bounds_2 = transformToRecLatticeCoordinates(qX, -qY, a, b, alpha);
    double qa_max = std::max(std::abs(q_bounds_1.first), std::abs(q_bounds_2.first));
    double qb_max = std::max(std::abs(q_bounds_1.second), std::abs(q_bounds_2.second));
    return {qa_max, qb_max};
}

std::pair<double, double> IFTDecayFunction2D::transformToRecLatticeCoordinates(double qX, double qY,
                                                                               double a, double b,
                                                                               double alpha) const
{
    double qa = (a * qX * std::cos(m_gamma) - a * qY * std::sin(m_gamma)) / M_TWOPI;
    double qb = (b * qX * std::cos(alpha - m_gamma) + b * qY * std::sin(alpha - m_gamma)) / M_TWOPI;
    return {qa, qb};
}

FTDecayFunction2DCauchy::FTDecayFunction2DCauchy(double decay_length_x, double decay_length_y,
                                                 double gamma)
    : IFTDecayFunction2D(decay_length_x, decay_length_y, gamma)
{
    setName("FTDecayFunction2DCauchy");
}

FTDecayFunction2DCauchy* FTDecayFunction2DCauchy::clone() const
{
    return new FTDecayFunction2DCauchy(m_decay_length_x, m_decay_length_y, m_gamma);
}

double FTDecayFunction2DCauchy::evaluate(double qx, double qy) const
{
    double sum_sq = qx * qx * m_decay_length_x * m_decay_length_x
                    + qy * qy * m_decay_length_y * m_decay_length_y;
    return M_TWOPI * m_decay_length_x * m_decay_length_y * std::pow(1.0 + sum_sq, -1.5);
}

FTDecayFunction2DGauss::FTDecayFunction2DGauss(double decay_length_x, double decay_length_y,
                                               double gamma)
    : IFTDecayFunction2D(decay_length_x, decay_length_y, gamma)
{
    setName("FTDecayFunction2DGauss");
}

FTDecayFunction2DGauss* FTDecayFunction2DGauss::clone() const
{
    return new FTDecayFunction2DGauss(m_decay_length_x, m_decay_length_y, m_gamma);
}

double FTDecayFunction2DGauss::evaluate(double qx, double qy) const
{
    double sum_sq = qx * qx * m_decay_length_x * m_decay_length_x
                    + qy * qy * m_decay_length_y * m_decay_length_y;
    return M_TWOPI * m_decay_length_x * m_decay_length_y * std::exp(-sum_sq / 2.0);
}

//! Constructor of two-dimensional pseudo-Voigt decay function in reciprocal space.
//! @param decay_length_x: the decay length in nanometers along x-axis of the distribution
//! @param decay_length_y: the decay length in nanometers along y-axis of the distribution
//! @param eta: parameter [0,1] to balance between Cauchy (eta=0.0) and Gauss (eta=1.0)
//! @param gamma: distribution orientation with respect to the first lattice vector in radians

FTDecayFunction2DVoigt::FTDecayFunction2DVoigt(double decay_length_x, double decay_length_y,
                                               double gamma, double eta)
    : IFTDecayFunction2D(decay_length_x, decay_length_y, gamma), m_eta(eta)
{
    setName("FTDecayFunction2DVoigt");
    registerParameter("Eta", &m_eta);
}

FTDecayFunction2DVoigt* FTDecayFunction2DVoigt::clone() const
{
    return new FTDecayFunction2DVoigt(m_decay_length_x, m_decay_length_y, m_eta, m_gamma);
}

double FTDecayFunction2DVoigt::evaluate(double qx, double qy) const
{
    double sum_sq = qx * qx * m_decay_length_x * m_decay_length_x
                    + qy * qy * m_decay_length_y * m_decay_length_y;
    return M_TWOPI * m_decay_length_x * m_decay_length_y
           * (m_eta * std::exp(-sum_sq / 2.0) + (1.0 - m_eta) * std::pow(1.0 + sum_sq, -1.5));
}
