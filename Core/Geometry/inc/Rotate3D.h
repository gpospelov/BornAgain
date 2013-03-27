// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file       Geometry/inc/Rotate3D.h
//! @brief      Defines and implements class Rotate3D.
//!
//! @homepage   http://apps.jcns.fz-juelich.de/BornAgain
//! @license    GNU General Public License v3 or higher (see COPYING)
//! @copyright  Forschungszentrum Jülich GmbH 2013
//! @authors    C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef GEOMETRY_ROTATE3D_H
#define GEOMETRY_ROTATE3D_H

#include "ITransform3D.h"

namespace Geometry {

//! Rotation around z axis.

class RotateZ_3D : public ITransform3D {
 public:
    //! Constructs a rotation by angle _a_.

    //! QUESTION: How can we construct identity transform for a=0?
    //!
    RotateZ_3D(double a)
        : m_ca( std::cos(a) ), m_sa( std::sin(a) ) {}

    //! Return inverse transform.
    RotateZ_3D inverse() const
    {
        RotateZ_3D ret;
        ret.sa = - ret.sa;
        return ret;
    }

    //! Return rotated vector _v_.
    template<class T>
    BasicVector3D<T> transformed(const BasicVector3D<T>& v) const
    {
        return BasicVector3D<T>( ca*v.x - sa*v.y,
                                 sa*v.x + ca*vx,
                                 v.z              );
    }

 private:
    double m_ca, m_sa;
}

}  // namespace Geometry

#endif /* GEOMETRY_ROTATE3D_H */
