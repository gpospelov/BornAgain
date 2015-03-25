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
    static IRotation *createRotation(const Geometry::Transform3D &transform);

    virtual ~IRotation() {}

    //! Returns a clone
    virtual IRotation *clone() const=0;

    //! Returns a clone with inverted magnetic fields
    virtual IRotation *cloneInvertB() const=0;

    //! Returns a new IRotation object that is the current object's inverse
    virtual IRotation *createInverse() const=0;

    //! Calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor* visitor) const { visitor->visit(this); }

    //! Returns transformation.
    virtual Geometry::Transform3D getTransform3D() const=0;
};

IRotation *CreateProduct(const IRotation& left, const IRotation &right);

class BA_CORE_API_ RotationX : public IRotation
{
public:
    RotationX(double angle);

    RotationX *clone() const;

    RotationX *cloneInvertB() const;

    RotationX *createInverse() const;

    Geometry::Transform3D getTransform3D() const;

protected:
    void init_parameters();

    double m_angle;
};

class BA_CORE_API_ RotationY : public IRotation
{
public:
    RotationY(double angle);

    RotationY *clone() const;

    RotationY *cloneInvertB() const;

    RotationY *createInverse() const;

    Geometry::Transform3D getTransform3D() const;

protected:
    void init_parameters();

    double m_angle;
};

class BA_CORE_API_ RotationZ : public IRotation
{
public:
    RotationZ(double angle);

    RotationZ *clone() const;

    RotationZ *cloneInvertB() const;

    RotationZ *createInverse() const;

    Geometry::Transform3D getTransform3D() const;

protected:
    void init_parameters();

    double m_angle;
};

class BA_CORE_API_ RotationEuler : public IRotation
{
public:
    RotationEuler(double alpha, double beta, double gamma);

    RotationEuler *clone() const;

    RotationEuler *cloneInvertB() const;

    IRotation *createInverse() const;

    Geometry::Transform3D getTransform3D() const;

protected:
    void init_parameters();

    double m_alpha, m_beta, m_gamma;
};


#endif // ROTATIONS_H


