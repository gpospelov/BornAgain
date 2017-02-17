// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Shapes/Dodecahedron.h
//! @brief     Defines class Dodecahedron.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DODECAHEDRON_H
#define DODECAHEDRON_H

#include "IShape.h"

class Dodecahedron : public IShape
{
public:
    Dodecahedron(double edge);
    ~Dodecahedron();
};

#endif // DODECAHEDRON_H
