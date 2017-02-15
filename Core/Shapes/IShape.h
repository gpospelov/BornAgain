// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/IShape.h
//! @brief     Defines interface IShape.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISHAPE_H
#define ISHAPE_H

#include "Vectors3D.h"
#include <vector>

class IShape
{
public:
    IShape() {}
    virtual ~IShape() {}

    //! Retrieves a list of the vertices constituting this concrete shape
    virtual std::vector<kvector_t> vertices() const;
protected:
    //! List of vertices initialized during construction
    std::vector<kvector_t> m_vertices;
};

#endif // ISHAPE_H
