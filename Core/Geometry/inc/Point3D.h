// ************************************************************************** //
//
//  heinzlibs:  Library collection of the Scientific Computing Group at
//              Heinz Maier-Leibnitz Zentrum (MLZ) Garching
//
//  libgeo3d:   Library for three-dimensional Euclidian geometry,
//              based on CLHEP/Geometry 1.9 of 1.4.2003,
//              forked after v 1.5 2010/06/16 16:21:27
//
//! @file       Geometry/inc/Point3D.h
//! @brief      defines class Point3D<double>, and implements most functions
//!
//! @homepage   http://apps.jcns.fz-juelich.de/BornAgain
//! @license    GNU General Public License v3 or higher (see COPYING)
//! @copyright  Forschungszentrum Jülich GmbH 2013
//! @authors    E. Chernyaev <Evgueni.Tcherniaev@cern.ch> 1996-2003
//! @authors    C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
//! Changes w.r.t. CLHEP:
//! - eliminated support for type float
//! - reworked doxygen comments
//
// ************************************************************************** //

#ifndef GEOMETRY_POINT3D_H
#define GEOMETRY_POINT3D_H

#include "BasicVector3D.h"

namespace Geometry {

class Transform3D;

//! A geometrical point in three dimensions with of templated coordinate type.

//! @author Evgeni Chernyaev 1996-2003
//!
template<class T>
class Point3D : public BasicVector3D<T> {};

//! A geometrical point in three dimensions, with double-precision coordinates.

//! @author Evgeni Chernyaev 1996-2003
//!
template<>
class Point3D<double> : public BasicVector3D<double> {
public:
    //! Default constructor.
    Point3D() {}
    //! Constructor from three numbers.
    Point3D(double x1, double y1, double z1)
        : BasicVector3D<double>(x1,y1,z1) {}
    //! Constructor from array of doubles.
    explicit Point3D(const double * a)
    : BasicVector3D<double>(a[0],a[1],a[2]) {}
    //! Copy constructor.
    Point3D(const Point3D<double> & v) : BasicVector3D<double>(v) {}
    //! Constructor from BasicVector3D<double>.
    Point3D(const BasicVector3D<double> & v) : BasicVector3D<double>(v) {}
    //! Destructor.
    ~Point3D() {}
    //! Assignment.
    Point3D<double> & operator=(const Point3D<double> & v) {
        setXYZ(v.x(),v.y(),v.z()); return *this; }
    //! Assignment from BasicVector3D<double>.
    Point3D<double> & operator=(const BasicVector3D<double> & v) {
        setXYZ(v.x(),v.y(),v.z()); return *this; }

    //! Returns distance to the origin squared.
    double distance2() const {
        return mag2(); }
    //! Returns distance to the point squared.
    double distance2(const Point3D<double> & p) const {
        double dx = p.x()-x(), dy = p.y()-y(), dz = p.z()-z();
        return dx*dx + dy*dy + dz*dz; }
    //! Returns distance to the origin.
    double distance() const {
        return std::sqrt(distance2()); }
    //! Returns distance to the point.
    double distance(const Point3D<double> & p) const {
        return std::sqrt(distance2(p)); }

    //! Transformation by Transform3D.
    Point3D<double> & transform(const Transform3D & m);
};

//! Transformation of Point3D<double> by Transform3D.

//! @relates Point3D
//!
Point3D<double>
operator*(const Transform3D & m, const Point3D<double> & p);

}  // namespace Geometry

#endif /* GEOMETRY_POINT3D_H */
