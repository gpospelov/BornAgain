// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Shapes/TruncatedCube.h
//! @brief     Defines class TruncatedCube.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TRUNCATEDCUBE_H
#define TRUNCATEDCUBE_H

#include "IShape.h"

class TruncatedCube : public IShape
{
public:
    TruncatedCube(double length, double removed_length);
    ~TruncatedCube();
};

#endif // TRUNCATEDCUBE_H
