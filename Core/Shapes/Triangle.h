// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Shapes/Triangle.h
//! @brief     Defines class Triangle.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "IShape.h"

class Triangle : public IShape
{
public:
    Triangle(double length, double z);
    ~Triangle();
};

#endif // TRIANGLE_H
