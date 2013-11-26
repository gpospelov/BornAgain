// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file       Geometry/inc/ITransform3D.h
//! @brief      Defines interface class ITransform3D.
//!
//! @homepage   http://apps.jcns.fz-juelich.de/BornAgain
//! @license    GNU General Public License v3 or higher (see COPYING)
//! @copyright  Forschungszentrum Jülich GmbH 2013
//! @authors    C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef GEOMETRY_ITRANSFROM3D_H
#define GEOMETRY_ITRANSFROM3D_H

#include "Types.h"
#include "BasicVector3D.h"
#include "EigenCore.h"
#include <boost/shared_ptr.hpp>


namespace Geometry {

//typedef boost::shared_ptr<class ITransform3D> PTransform3D;

//! Interface to vector transforms in three dimensions.

class ITransform3D {
public:

    virtual ~ITransform3D() {}

    //! Returns the inverse transformation.
    virtual ITransform3D *inverse() const
    { return new ITransform3D(); }

    //! Return transformed vector _v_.
    virtual BasicVector3D<double>
        transformed(const BasicVector3D<double>& v) const
    { return v; }

    //! Return transformed vector _v_.
    virtual BasicVector3D<complex_t>
        transformed(const BasicVector3D<complex_t>& v) const
    { return v; }

    virtual ITransform3D *clone() const { return new ITransform3D(); }

#ifndef GCCXML_SKIP_THIS
    Eigen::Matrix2cd transformed(const Eigen::Matrix2cd &m) const;
#endif

    friend std::ostream& operator<<(std::ostream& ostr, const ITransform3D& m)
    { m.print(ostr); return ostr; }

    virtual void print(std::ostream& ostr) const
    { ostr << "Transform3D:Identity"; }
};

}// namespace Geometry

inline Eigen::Matrix2cd Geometry::ITransform3D::transformed(
        const Eigen::Matrix2cd& m) const
{
    Eigen::Matrix2cd result;
    complex_t im(0.0, 1.0);
    double a = std::real(m(0,0) + m(1,1))/2.0;
    double bx = std::real(m(1,0));
    double by = std::imag(m(1,0));
    double bz = std::real(m(0,0) - m(1,1))/2.0;
    BasicVector3D<double> b_v(bx, by, bz);
    BasicVector3D<double> b_v_t = transformed(b_v);
    result(0,0) = a + b_v_t.z();
    result(0,1) = b_v_t.x() - im*b_v_t.y();
    result(1,0) = b_v_t.x() + im*b_v_t.y();
    result(1,1) = a - b_v_t.z();
    return result;
}

#endif /* GEOMETRY_ITRANSFROM3D_H */


