//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      Sample/Shapes/IShape3D.h
//! @brief     Defines interface IShape3D.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_SAMPLE_SHAPES_ISHAPE_H
#define BORNAGAIN_SAMPLE_SHAPES_ISHAPE_H

#include "Base/Vector/Vectors3D.h"
#include <vector>

//! Abstract base class for different shapes.
//!
//! In contrast to the form factors, these shapes only provide an interface
//! for returning a set of vertices.

//! @ingroup shapes_internal

class IShape3D {
public:
    IShape3D() {}
    virtual ~IShape3D() {}

    //! Retrieves a list of the vertices constituting this concrete shape
    virtual std::vector<kvector_t> vertices() const;
    static const size_t N_Circle;

protected:
    //! List of vertices initialized during construction
    std::vector<kvector_t> m_vertices;
};

//! Helper functions to construct lists of vertices
//!
//! Generate vertices of centered rectangle at height z
std::vector<kvector_t> RectangleVertices(double length, double width, double z);

//! Generate vertices of centered ellipse with given semi-axes at height z
std::vector<kvector_t> EllipseVertices(double r_x, double r_y, double z);

#endif // BORNAGAIN_SAMPLE_SHAPES_ISHAPE_H
#endif // USER_API
