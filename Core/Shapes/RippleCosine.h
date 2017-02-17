// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Shapes/RippleCosine.h
//! @brief     Defines class RippleCosine.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef RIPPLECOSINE_H
#define RIPPLECOSINE_H

#include "IShape.h"

class RippleCosine : public IShape
{
public:
    RippleCosine(double length, double width, double height);
    ~RippleCosine();
};

#endif // RIPPLECOSINE_H
