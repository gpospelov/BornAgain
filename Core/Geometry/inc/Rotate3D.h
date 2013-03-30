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

//! Rotation around y axis.

class RotateY_3D : public ITransform3D {
 public:
    //! Constructs a rotation by angle _a_.

    //! QUESTION: How can we construct identity transform for a=0?
    //!
    RotateY_3D(double a)
        : m_ca( std::cos(a) ), m_sa( std::sin(a) ) {}

    virtual ~RotateY_3D() {}

    //! Return inverse transform.
    PTransform3D inverse() const
    { return PTransform3D( new RotateY_3D( m_ca, -m_sa ) ); }

    //! Return rotated vector _v_.
    BasicVector3D<double> transformed(const BasicVector3D<double>& v) const
    {   return BasicVector3D<double>( m_ca*v.x() + m_sa*v.z(),
                                      v.y(),
                                     -m_sa*v.x() + m_ca*v.z() );
    }

    //! Return rotated vector _v_: avoid complex implementation unless needed.

    //! QUESTION: Can we avoid this duplication, using template?
    //!
    BasicVector3D<complex_t>
        transformed(const BasicVector3D<complex_t>& v) const
    {   return BasicVector3D<complex_t>( m_ca*v.x() + m_sa*v.z(),
                                         v.y(),
                                        -m_sa*v.x() + m_ca*v.z() );
    }

    virtual void print(std::ostream& ostr) const
    { ostr << "Transform3D:Rotate_Y(" << m_ca << "," << m_sa << ")" ; }

 private:
    double m_ca, m_sa;

    //! Constructs a rotation by angle _a_ from cos(a) and sin(a).
    RotateY_3D(double cos_a, double sin_a)
        : m_ca(cos_a), m_sa(sin_a) {}
};

//! Rotation around z axis.

class RotateZ_3D : public ITransform3D {
 public:
    //! Constructs a rotation by angle _a_.

    RotateZ_3D(double a)
        : m_ca( std::cos(a) ), m_sa( std::sin(a) ) {}

    virtual ~RotateZ_3D() {}

    //! Return inverse transform.
    virtual PTransform3D inverse() const
    { return PTransform3D( new RotateZ_3D( m_ca, -m_sa )); }

    //! Return rotated vector _v_.
    virtual BasicVector3D<double> transformed(const BasicVector3D<double>& v) const
    {   return BasicVector3D<double>( m_ca*v.x() - m_sa*v.y(),
                                      m_sa*v.x() + m_ca*v.y(),
                                      v.z()                    );
    }

    //! Return rotated vector _v_: avoid complex implementation unless needed.
    virtual BasicVector3D<complex_t>
        transformed(const BasicVector3D<complex_t>& v) const
    {   return BasicVector3D<complex_t>( m_ca*v.x() - m_sa*v.y(),
                                         m_sa*v.x() + m_ca*v.y(),
                                         v.z()                    );
    }

    virtual void print(std::ostream& ostr) const
    { ostr << "Transform3D:Rotate_Z(" << m_ca << "," << m_sa << ")" ; }

 private:
    double m_ca, m_sa;

    //! Constructs a rotation by angle _a_ from cos(a) and sin(a).
    RotateZ_3D(double cos_a, double sin_a)
        : m_ca(cos_a), m_sa(sin_a) {}
};

}  // namespace Geometry

#endif /* GEOMETRY_ROTATE3D_H */
