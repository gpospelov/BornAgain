// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Shapes/Icosahedron.h
//! @brief     Defines class Icosahedron.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ICOSAHEDRON_H
#define ICOSAHEDRON_H

#include "IShape.h"

class Icosahedron : public IShape
{
public:
    Icosahedron(double edge);
    ~Icosahedron();
};

#endif // ICOSAHEDRON_H
