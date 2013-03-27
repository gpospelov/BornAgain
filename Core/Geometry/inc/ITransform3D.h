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

#include "BasicVector3D.h"

namespace Geometry {

//! Interface to vector transforms in three dimensions.

class ITransform3D {
 public:
    //! Default constructor, sets the identity transformation.
    ITransform3D() {}

    virtual ~ITransform3D() {}

    //! Returns the inverse transformation.
    virtual ITransform3D inverse() const
    { return *this; }
    
    //! Return transformed vector _v_.
    virtual BasicVector3D<double>
        transformed(const BasicVector3D<double>& v) const
    { return v; }

    //! Return transformed vector _v_.
    virtual BasicVector3D<complex_t>
        transformed(const BasicVector3D<complex_t>& v) const
    { return v; }

};
 
}  // namespace Geometry

#endif /* GEOMETRY_ITRANSFROM3D_H */
