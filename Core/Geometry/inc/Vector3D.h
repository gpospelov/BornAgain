// ************************************************************************** //
//
//  heinzlibs:  Library collection of the Scientific Computing Group at
//              Heinz Maier-Leibnitz Zentrum (MLZ) Garching
//
//  libgeo3d:   Library for three-dimensional Euclidian geometry,
//              based on CLHEP/Geometry 1.9 of 1.4.2003,
//              forked after v 1.3 2003/10/23 21:29:50
//
//! @file       Geometry/inc/Vector3D.h
//! @brief      defines class Vector3D<double>, and implements most functions
//!
//! @homepage   http://apps.jcns.fz-juelich.de/BornAgain
//! @license    GNU General Public License v3 or higher (see COPYING)
//! @copyright  Forschungszentrum Jülich GmbH 2013
//! @authors    Evgeni Chernyaev <Evgueni.Tcherniaev@cern.ch> 1996-2003
//! @authors    C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//!
//! Changes w.r.t. CLHEP:
//! - eliminated support for type float
//! - reworked doxygen comments
//
// ************************************************************************** //

#ifndef GEOMETRY_VECTOR3D_H
#define GEOMETRY_VECTOR3D_H

//#include <iosfwd>
//#include "CLHEP/Geometry/defs.h"
//#include "CLHEP/Vector/ThreeVector.h"
//#include "CLHEP/Geometry/BasicVector3D.h"
#include "BasicVector3D.h"

namespace Geometry {

class Transform3D;

//! Geometrical 3D Vector.

//! This is just a declaration of the class needed to define
//! specialization Vector3D<double>.
//!
//! @author Evgeni Chernyaev <Evgueni.Tcherniaev@cern.ch> 1996-2003

template<class T>
class Vector3D : public BasicVector3D<T> {};

//! Geometrical 3D Vector with components of double type.
//!
//! @author Evgeni Chernyaev <Evgueni.Tcherniaev@cern.ch>

template<>
class Vector3D<double> : public BasicVector3D<double> {
public:
    
    //! Default constructor.
    Vector3D() {}
    
    //! Constructor from three numbers.
    Vector3D(double x1, double y1, double z1)
        : BasicVector3D<double>(x1,y1,z1) {}

    //! Constructor from array of doubles.
    explicit Vector3D(const double * a)
        : BasicVector3D<double>(a[0],a[1],a[2]) {}
    
    //! Copy constructor.
    Vector3D(const Vector3D<double> & v)
        : BasicVector3D<double>(v) {}

    //! Constructor from BasicVector3D<double>.
    Vector3D(const BasicVector3D<double> & v)
        : BasicVector3D<double>(v) {}
    
    //! Destructor.
    ~Vector3D() {}

    //! Assignment.
    Vector3D<double> & operator=(const Vector3D<double> & v)
        { setXYZ(v.x(),v.y(),v.z()); return *this; }

    //! Assignment from BasicVector3D<double>.
    Vector3D<double> & operator=(const BasicVector3D<double> & v)
        { setXYZ(v.x(),v.y(),v.z()); return *this; }
    
    //! Transformation by Transform3D.
    Vector3D<double> & transform(const Transform3D & m);
};


//! Transformation of Vector<double> by Transform3D.
//! @relates Vector3D

Vector3D<double>
operator*(const Transform3D & m, const Vector3D<double> & v);

}  // namespace Geometry

#endif /* GEOMETRY_VECTOR3D_H */
