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
#include "Macros.h"
GCC_DIAG_OFF(unused-local-typedefs);
#include <boost/shared_ptr.hpp>
GCC_DIAG_ON(unused-local-typedefs);

namespace Geometry {

typedef boost::shared_ptr<class ITransform3D> PTransform3D;

//! Interface to vector transforms in three dimensions.

class ITransform3D {
 public:

    virtual ~ITransform3D() {}

    //! Returns the inverse transformation.
    virtual PTransform3D inverse() const
    { return PTransform3D( new ITransform3D() ); }
  
    //! Return transformed vector _v_.
    virtual BasicVector3D<double>
        transformed(const BasicVector3D<double>& v) const
    { return v; }

    //! Return transformed vector _v_.
    virtual BasicVector3D<complex_t>
        transformed(const BasicVector3D<complex_t>& v) const
    { return v; }

    friend std::ostream& operator<<(std::ostream& ostr, const ITransform3D& m)
    { m.print(ostr); return ostr; }

    virtual void print(std::ostream& ostr) const
    { ostr << "Transform3D:Identity"; }

};


//class PTransform3DWrapper {
//public:

//    PTransform3D
//};

}  // namespace Geometry

#endif /* GEOMETRY_ITRANSFROM3D_H */


