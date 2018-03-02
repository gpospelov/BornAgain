// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Shapes/Triangle.h
//! @brief     Defines class Triangle.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
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
