// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Shapes/Icosahedron.h
//! @brief     Defines class Icosahedron.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
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
