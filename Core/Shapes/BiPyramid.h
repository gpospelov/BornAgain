// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Shapes/BiPyramid.h
//! @brief     Defines class BiPyramid.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef BIPYRAMID_H
#define BIPYRAMID_H

#include "IShape.h"

class BiPyramid : public IShape
{
public:
    BiPyramid(double length, double height, double height_ratio, double alpha);
    ~BiPyramid();
};

#endif // BIPYRAMID_H
