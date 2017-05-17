// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Shapes/TruncatedEllipsoid.h
//! @brief     Defines class TruncatedEllipsoid.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TRUNCATEDELLIPSOID_H
#define TRUNCATEDELLIPSOID_H

#include "IShape.h"

class TruncatedEllipsoid : public IShape
{
public:
    TruncatedEllipsoid(double r_x, double r_y, double r_z, double height, double dh);
    ~TruncatedEllipsoid();
};

#endif // TRUNCATEDELLIPSOID_H
