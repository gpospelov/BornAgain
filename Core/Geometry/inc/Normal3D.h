// ************************************************************************** //
//
//  heinzlibs:  Library collection of the Scientific Computing Group at
//              Heinz Maier-Leibnitz Zentrum (MLZ) Garching
//
//  libgeo3d:   Library for three-dimensional Euclidian geometry,
//              based on CLHEP/Geometry 1.9 of 1.4.2003,
//              forked after v 1.3 2003/10/23 21:29:50
//
//! @file       Geometry/inc/Normal3D.h
//! @brief      defines class Normal3D<double>, and implements most functions
//!
//! @homepage   http://apps.jcns.fz-juelich.de/BornAgain
//! @license    GNU General Public License v3 or higher (see COPYING)
//! @copyright  Forschungszentrum Jülich GmbH 2013
//! @authors    E. Chernyaev <Evgueni.Tcherniaev@cern.ch> 1996-2003
//! @authors    C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//!
//! Changes w.r.t. CLHEP:
//! - eliminated support for type float
//! - reworked doxygen comments
//
// ************************************************************************** //

#ifndef GEOMETRY_NORMAL3D_H
#define GEOMETRY_NORMAL3D_H

#include "BasicVector3D.h"

namespace Geometry {

class Transform3D;

//! A three-dimensional normal vector of templated coordinate type.
    
//! Note that this is not a unit vector.
//! It seems to be a regular vector, except for the behaviour under
//! reflection and scaling.
//!
//! @author Evgeni Chernyaev <Evgueni.Tcherniaev@cern.ch> 1996-2003
//!
template<class T>
class Normal3D : public BasicVector3D<T> {};


//! A three-dimensional normal vector with double-precision coordinates.

//! @author Evgeni Chernyaev <Evgueni.Tcherniaev@cern.ch> 1996-2003
//!
template<>
class Normal3D<double> : public BasicVector3D<double> {
public:

    //! Default constructor.
    Normal3D() {}
    //! Constructor from three numbers.
    Normal3D(double x1, double y1, double z1)
        : BasicVector3D<double>(x1,y1,z1) {}

    //! Constructor from array of doubles.
    explicit Normal3D(const double* a)
    : BasicVector3D<double>(a[0],a[1],a[2]) {}

    //! Constructor from BasicVector3D<double>.
    Normal3D(const BasicVector3D<double>& v)
        : BasicVector3D<double>(v) {}

    //! Copy constructor.
    Normal3D(const Normal3D<double>& v)
        : BasicVector3D<double>(v) {}

    //! Destructor.
    ~Normal3D() {}

    //! Assignment.
    Normal3D<double>& operator=(const Normal3D<double>& v)
        { setXYZ(v.x(),v.y(),v.z()); return *this; }

    //! Assignment from BasicVector3D<double>.
    Normal3D<double>& operator=(const BasicVector3D<double>& v)
        { setXYZ(v.x(),v.y(),v.z()); return *this; }

    //! Transformation by Transform3D.
    Normal3D<double>& transform(const Transform3D& m);
};

//! Transformation of Normal<double> by Transform3D.

//! @relates Normal3D
//!
Normal3D<double>
operator*(const Transform3D & m, const Normal3D<double> & n);

}  // namespace Geometry

#endif /* GEOMETRY_NORMAL3D_H */
