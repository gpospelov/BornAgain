#ifndef FORMFACTORDECORATORTRANSFORMATION_H
#define FORMFACTORDECORATORTRANSFORMATION_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   FormFactorDecoratorFactor.h
//! @brief  Definition of FormFactorDecoratorFactor class
//! @author Scientific Computing Group at FRM II
//! @date   Jun 29, 2012

#include "IFormFactor.h"
#include "Transform3D.h"


class FormFactorDecoratorTransformation : public IFormFactorDecorator
{
public:
    FormFactorDecoratorTransformation(IFormFactor *p_form_factor, Geometry::Transform3D *transform);
    virtual FormFactorDecoratorTransformation *clone() const;
    virtual ~FormFactorDecoratorTransformation();

    virtual complex_t evaluate(const cvector_t &k_i, const cvector_t &k_f, double alpha_i, double alpha_f) const;
    virtual int getNumberOfStochasticParameters() const;

protected:
    Geometry::Transform3D *mp_transform;
    Geometry::Transform3D *mp_inverse_transform;
};

inline FormFactorDecoratorTransformation::FormFactorDecoratorTransformation(
        IFormFactor* p_form_factor, Geometry::Transform3D *transform)
: IFormFactorDecorator(p_form_factor)
, mp_transform(transform)
, mp_inverse_transform(0)
{
    mp_inverse_transform = new Geometry::Transform3D(mp_transform->inverse());
}

inline FormFactorDecoratorTransformation* FormFactorDecoratorTransformation::clone() const
{
    Geometry::Transform3D *p_new_transform = new Geometry::Transform3D(*mp_transform);
    return new FormFactorDecoratorTransformation(mp_form_factor->clone(), p_new_transform);
}

inline FormFactorDecoratorTransformation::~FormFactorDecoratorTransformation()
{
    delete mp_transform;
    delete mp_inverse_transform;
}

inline complex_t FormFactorDecoratorTransformation::evaluate(const cvector_t &k_i, const cvector_t &k_f,
        double alpha_i, double alpha_f) const
{
    cvector_t newki(k_i);
    cvector_t newkf(k_f);
    newki.transform(*mp_inverse_transform);
    newkf.transform(*mp_inverse_transform);
    return mp_form_factor->evaluate(newki, newkf, alpha_i, alpha_f);
}

inline int FormFactorDecoratorTransformation::getNumberOfStochasticParameters() const
{
    return mp_form_factor->getNumberOfStochasticParameters();
}

#endif // FORMFACTORDECORATORTRANSFORMATION_H
