// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file       Geometry/inc/Transform3D.h
//! @brief      Defines class Transform3D.
//!
//! @homepage   http://apps.jcns.fz-juelich.de/BornAgain
//! @license    GNU General Public License v3 or higher (see COPYING)
//! @copyright  Forschungszentrum Jülich GmbH 2013
//! @authors    C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef GEOMETRY_TRANSFORM3D_H
#define GEOMETRY_TRANSFORM3D_H

#include "Types.h"
#include "BasicVector3D.h"
#include "EigenCore.h"


namespace Geometry {

//! @class Transform3D
//! @ingroup tools_internal
//! @brief Vector transformations in three dimensions.

class Transform3D {
public:
    //! Constructs unit transformation
    Transform3D();

    //! Copy constructor
    Transform3D(const Transform3D& other);

    //! Destructor
    ~Transform3D() {}

    //! Clones the transformation
    Transform3D *clone() const;

    //! Creates identity transformation (default)
    static Transform3D createIdentity();

    //! Creates rotation around x-axis
    static Transform3D createRotateX(double phi);

    //! Creates rotation around y-axis
    static Transform3D createRotateY(double phi);

    //! Creates rotation around z-axis
    static Transform3D createRotateZ(double phi);

    //! Returns the inverse transformation.
    Transform3D *createInverse() const;

    //! Return transformed vector _v_.
    BasicVector3D<double>
        transformed(const BasicVector3D<double>& v) const;

    //! Return transformed vector _v_.
    BasicVector3D<complex_t>
        transformed(const BasicVector3D<complex_t>& v) const;

    //! Return transformed vector _v_.
    BasicVector3D<double>
        transformedInverse(const BasicVector3D<double>& v) const;

    //! Return transformed vector _v_.
    BasicVector3D<complex_t>
        transformedInverse(const BasicVector3D<complex_t>& v) const;

    //! Composes two transformations
    Transform3D operator*(const Transform3D &other) const;

    friend std::ostream& operator<<(std::ostream& ostr, const Transform3D& m)
    { m.print(ostr); return ostr; }

    void print(std::ostream& ostr) const;

private:
#ifndef GCCXML_SKIP_THIS
    Transform3D(const Eigen::Matrix3d &matrix);
    Eigen::Matrix3d m_matrix;
    Eigen::Matrix3d m_inverse_matrix;
#endif
};

}// namespace Geometry

#endif /* GEOMETRY_TRANSFORM3D_H */


