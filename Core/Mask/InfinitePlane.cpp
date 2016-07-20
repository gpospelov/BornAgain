// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Mask/InfinitePlane.cpp
//! @brief     Implements class InfinitePlane.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "InfinitePlane.h"

namespace Geometry {

InfinitePlane *InfinitePlane::clone() const
{
    return new InfinitePlane();
}

bool InfinitePlane::contains(double x, double y) const
{
    (void)x;
    (void)y;
    return true;
}

bool InfinitePlane::contains(const Bin1D &binx, const Bin1D &biny) const
{
    (void)binx;
    (void)biny;
    return true;
}


} // namespace Geometry
