// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Shapes/Pyramid6.h
//! @brief     Defines class Pyramid6.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PYRAMID6_H
#define PYRAMID6_H

#include "IShape.h"

class Pyramid6 : public IShape
{
public:
    Pyramid6(double length, double height, double alpha);
    ~Pyramid6();
private:
    static const double sqrt3;
};

#endif // PYRAMID6_H
