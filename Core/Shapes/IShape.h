// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Shapes/IShape.h
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

//! Pure virtual base class for different shapes.
//!
//! In contrast to the form factors, these shapes only provide an intereface
//! for returning a set of vertices.

//! @ingroup shapes_internal

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

//! Helper functions to construct lists of vertices
//!
//! Generate vertices of centered rectangle at height z
std::vector<kvector_t> RectangleVertices(double length, double width, double z);

//! Generate vertices of centered regular triangle with vertex on x-axis at height z
std::vector<kvector_t> TriangleVertices(double length, double z);

#endif // ISHAPE_H
