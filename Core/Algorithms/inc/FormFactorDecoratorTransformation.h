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


class FormFactorDecoratorTransformation : public IFormFactor
{
public:
    FormFactorDecoratorTransformation(IFormFactor *p_form_factor, Geometry::Transform3D *transform);
    virtual FormFactorDecoratorTransformation *clone() const;
    virtual ~FormFactorDecoratorTransformation();

    virtual complex_t evaluate(kvector_t k_i, kvector_t k_f) const;
    virtual complex_t evaluateForComplexkz(kvector_t k_i, kvector_t k_f, complex_t k_iz, complex_t k_fz) const;
    virtual int getNumberOfStochasticParameters() const;

protected:
    Geometry::Transform3D *m_transform;
    IFormFactor *mp_form_factor;
};

inline FormFactorDecoratorTransformation::FormFactorDecoratorTransformation(
        IFormFactor* p_form_factor, Geometry::Transform3D *transform)
: m_transform(transform)
, mp_form_factor(p_form_factor)
{
}

inline FormFactorDecoratorTransformation* FormFactorDecoratorTransformation::clone() const
{
    Geometry::Transform3D *transform = new Geometry::Transform3D(*m_transform);
    return new FormFactorDecoratorTransformation(mp_form_factor->clone(), transform);
}

inline FormFactorDecoratorTransformation::~FormFactorDecoratorTransformation()
{
    delete m_transform;
    delete mp_form_factor;
}

inline complex_t FormFactorDecoratorTransformation::evaluate(kvector_t k_i,
        kvector_t k_f) const
{
    return mp_form_factor->evaluate(k_i, k_f);
}

inline complex_t FormFactorDecoratorTransformation::evaluateForComplexkz(kvector_t k_i,
        kvector_t k_f, complex_t k_iz, complex_t k_fz) const
{
//    Geometry::Vector3D<double> vki( k_i.x(), k_i.y(), k_i.z() );
//    Geometry::Vector3D<double> vkf( k_f.x(), k_f.y(), k_f.z() );
//    vki = *m_transform*vki;
//    vkf = *m_transform*vkf;
//    k_i.setXYZ(vki.x(), vki.y(), vki.z() );
//    k_f.setXYZ(vkf.x(), vkf.y(), vkf.z() );
//    k_i = *m_transform*k_i;
//    k_f = *m_transform*k_f;
    k_i.transform(*m_transform);
    k_f.transform(*m_transform);
    return mp_form_factor->evaluateForComplexkz(k_i, k_f, k_iz, k_fz);
}

inline int FormFactorDecoratorTransformation::getNumberOfStochasticParameters() const
{
    return mp_form_factor->getNumberOfStochasticParameters();
}

#endif // FORMFACTORDECORATORTRANSFORMATION_H
