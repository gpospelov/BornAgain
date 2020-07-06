// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/ResolutionFunction2DGaussian.cpp
//! @brief     Implements class ResolutionFunction2DGaussian.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Instrument/ResolutionFunction2DGaussian.h"
#include "Core/Basics/BornAgainNamespace.h"
#include "Core/Parametrization/RealParameter.h"
#include "Core/Tools/MathFunctions.h"

ResolutionFunction2DGaussian::ResolutionFunction2DGaussian(double sigma_x, double sigma_y)
    : m_sigma_x(sigma_x), m_sigma_y(sigma_y)
{
    setName(BornAgain::ResolutionFunction2D);
    registerParameter(BornAgain::SigmaX, &m_sigma_x).setNonnegative();
    registerParameter(BornAgain::SigmaY, &m_sigma_y).setNonnegative();
}

double ResolutionFunction2DGaussian::evaluateCDF(double x, double y) const
{
    return MathFunctions::IntegratedGaussian(x, 0.0, m_sigma_x)
           * MathFunctions::IntegratedGaussian(y, 0.0, m_sigma_y);
}
