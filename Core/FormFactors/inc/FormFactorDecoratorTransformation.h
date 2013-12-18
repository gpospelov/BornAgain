// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorDecoratorTransformation.h
//! @brief     Defines class FormFactorDecoratorTransformation.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORDECORATORTRANSFORMATION_H
#define FORMFACTORDECORATORTRANSFORMATION_H

#include "IFormFactorDecorator.h"
#include "ITransform3D.h"
#include <memory>

//! @class FormFactorDecoratorTransformation
//! @ingroup formfactors_internal
//! @brief Equip a formfactor with a rotation.

class FormFactorDecoratorTransformation : public IFormFactorDecorator
{
public:
    //! Constructor, setting form factor and rotation.
    FormFactorDecoratorTransformation(
        IFormFactor *p_form_factor, const Geometry::ITransform3D& transform)
        : IFormFactorDecorator(p_form_factor)
        , mP_transform(0)
        , mP_inverse_transform(0)
    {
        setName("FormFactorDecoratorTransformation");
        mP_transform.reset(transform.clone());
        mP_inverse_transform.reset(mP_transform->inverse());
    }

    virtual ~FormFactorDecoratorTransformation() {}

    virtual FormFactorDecoratorTransformation *clone() const;
    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    virtual complex_t evaluate(const cvector_t& k_i,
            const Bin1DCVector& k_f_bin, Bin1D alpha_f_bin) const;

    virtual int getNumberOfStochasticParameters() const
    { return mp_form_factor->getNumberOfStochasticParameters(); }

protected:
    std::auto_ptr<Geometry::ITransform3D> mP_transform;
    std::auto_ptr<Geometry::ITransform3D> mP_inverse_transform;
};


inline complex_t FormFactorDecoratorTransformation::evaluate(
    const cvector_t& k_i, const Bin1DCVector& k_f_bin, Bin1D alpha_f_bin) const
{
    cvector_t new_ki =
        mP_inverse_transform->transformed(k_i);
    cvector_t new_kf_lower =
        mP_inverse_transform->transformed(k_f_bin.m_q_lower);
    cvector_t new_kf_upper =
        mP_inverse_transform->transformed(k_f_bin.m_q_upper);
    Bin1DCVector new_kf_bin(new_kf_lower, new_kf_upper);
    return mp_form_factor->evaluate(new_ki, new_kf_bin, alpha_f_bin);
}

#endif // FORMFACTORDECORATORTRANSFORMATION_H


