// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/FormFactorDecoratorTransformation.h
//! @brief     Defines class FormFactorDecoratorTransformation.
//!
//! @homepage  apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef FORMFACTORDECORATORTRANSFORMATION_H
#define FORMFACTORDECORATORTRANSFORMATION_H

#include "IFormFactorDecorator.h"
#include "Transform3D.h"

//! ?

class FormFactorDecoratorTransformation : public IFormFactorDecorator
{
public:
    FormFactorDecoratorTransformation(IFormFactor *p_form_factor, Geometry::Transform3D *transform);
    virtual FormFactorDecoratorTransformation *clone() const;
    virtual ~FormFactorDecoratorTransformation();

    virtual complex_t evaluate(const cvector_t &k_i, const Bin1DCVector &k_f_bin, double alpha_i, double alpha_f) const;

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
    setName("FormFactorDecoratorTransformation");
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

inline complex_t FormFactorDecoratorTransformation::evaluate(const cvector_t& k_i, const Bin1DCVector& k_f_bin,
        double alpha_i, double alpha_f) const
{
    cvector_t new_ki(k_i);
    cvector_t new_kf_lower(k_f_bin.m_q_lower);
    cvector_t new_kf_upper(k_f_bin.m_q_upper);
    new_ki.transform(*mp_inverse_transform);
    new_kf_lower.transform(*mp_inverse_transform);
    new_kf_upper.transform(*mp_inverse_transform);
    Bin1DCVector new_kf_bin(new_kf_lower, new_kf_upper);
    return mp_form_factor->evaluate(new_ki, new_kf_bin, alpha_i, alpha_f);
}

inline int FormFactorDecoratorTransformation::getNumberOfStochasticParameters() const
{
    return mp_form_factor->getNumberOfStochasticParameters();
}

#endif // FORMFACTORDECORATORTRANSFORMATION_H
