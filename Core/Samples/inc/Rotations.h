// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/Rotations.h
//! @brief     Defines IRotation classes.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ROTATIONS_H
#define ROTATIONS_H

#include "ISample.h"
#include "Transform3D.h"

#include <memory>

//! @class IRotation
//! @ingroup samples
//! @brief An interface for classes representing a rotation

class BA_CORE_API_ IRotation : public ISample
{
public:
    virtual ~IRotation() {}

    //! Returns a clone
    virtual IRotation *clone() const=0;

    //! Returns a clone with inverted magnetic fields
    virtual IRotation *cloneInvertB() const=0;

    //! Calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor* visitor) const { visitor->visit(this); }

    //! Returns transformation.
    virtual Geometry::Transform3D *getTransform3D() const=0;
};


class BA_CORE_API_ RotationX : public IRotation
{
public:
    RotationX(double angle);

    RotationX *clone() const;

    RotationX *cloneInvertB() const;

    Geometry::Transform3D *getTransform3D() const;

protected:
    void init_parameters();

    double m_angle;
};


#endif // ROTATIONS_H


