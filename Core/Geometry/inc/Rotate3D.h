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

    //! Return inverse transform.
    virtual PTransform3D inverse() const
    { return new PTransform3D( RotateY_3D( m_ca, -m_sa ) ); }

    //! Return rotated vector _v_.
    virtual BasicVector3D<double> transformed(const BasicVector3D<double>& v) const
    {   std::cout << "DEBUG: trafo<double> rotate y\n"; 
        return BasicVector3D<double>( m_ca*v.x() + m_sa*v.z(),
                                      v.y(),
                                      -m_sa*v.x() + m_ca*v.z() );
    }

    //! Return rotated vector _v_: avoid complex implementation unless needed.
    virtual BasicVector3D<complex_t>
        transformed(const BasicVector3D<complex_t>& v) const
    { (void)v;  // to prevent unused-variable warning
        throw NotImplementedException("Rotate_3D::transformed<complex_t> -> "
                                    "not implemented" );
    }

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

    //! Return inverse transform.
    virtual ITransform3D inverse() const
    { return RotateZ_3D( m_ca, -m_sa ); }

    //! Return rotated vector _v_.
    virtual BasicVector3D<double> transformed(const BasicVector3D<double>& v) const
    {   std::cout << "DEBUG: trafo<double> rotate z\n"; 
        return BasicVector3D<double>( m_ca*v.x() - m_sa*v.y(),
                                      m_sa*v.x() + m_ca*v.y(),
                                      v.z()                    );
    }

    //! Return rotated vector _v_: avoid complex implementation unless needed.
    virtual BasicVector3D<complex_t>
        transformed(const BasicVector3D<complex_t>& v) const
    { (void)v;  // to prevent unused-variable warning
        throw NotImplementedException("RotateZ_3D::transformed<complex_t> -> "
                                    "not implemented" );
    }

 private:
    double m_ca, m_sa;

    //! Constructs a rotation by angle _a_ from cos(a) and sin(a).
    RotateZ_3D(double cos_a, double sin_a)
        : m_ca(cos_a), m_sa(sin_a) {}
};

}  // namespace Geometry

#endif /* GEOMETRY_ROTATE3D_H */
