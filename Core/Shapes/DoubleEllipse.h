// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Shapes/DoubleEllipse.h
//! @brief     Defines class DoubleEllipse.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DOUBLEELLIPSE_H
#define DOUBLEELLIPSE_H

#include "IShape.h"

class DoubleEllipse : public IShape
{
public:
    DoubleEllipse(double r0_x, double r0_y, double z, double rz_x, double rz_y);
    ~DoubleEllipse();
};

#endif // DOUBLEELLIPSE_H
