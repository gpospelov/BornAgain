// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorDecoratorRotation.h
//! @brief     Defines class FormFactorDecoratorRotation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORDECORATORROTATION_H
#define FORMFACTORDECORATORROTATION_H

#include "IFormFactorDecorator.h"
#include "Rotations.h"
#include <memory>

//! @class FormFactorDecoratorRotation
//! @ingroup formfactors_internal
//! @brief Equips a formfactor with a rotation.

class BA_CORE_API_ FormFactorDecoratorRotation : public IFormFactorDecorator
{
public:
    //! Constructor, setting form factor and rotation.
    FormFactorDecoratorRotation(
        const IFormFactor& form_factor, const IRotation& transform)
        : IFormFactorDecorator(form_factor.clone())
    {
        setName("FormFactorDecoratorRotation");
        m_transform = transform.getTransform3D();
    }

    virtual ~FormFactorDecoratorRotation() {}

    virtual FormFactorDecoratorRotation *clone() const;
    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    virtual complex_t evaluate(const cvector_t& k_i,
            const Bin1DCVector& k_f_bin, const Bin1D &alpha_f_bin) const;

    virtual int getNumberOfStochasticParameters() const
    { return mp_form_factor->getNumberOfStochasticParameters(); }

protected:
    Geometry::Transform3D m_transform;
};


inline complex_t FormFactorDecoratorRotation::evaluate(
    const cvector_t& k_i, const Bin1DCVector& k_f_bin, const Bin1D &alpha_f_bin) const
{
    cvector_t new_ki =
        m_transform.transformedInverse(k_i);
    cvector_t new_kf_lower =
        m_transform.transformedInverse(k_f_bin.m_q_lower);
    cvector_t new_kf_upper =
        m_transform.transformedInverse(k_f_bin.m_q_upper);
    Bin1DCVector new_kf_bin(new_kf_lower, new_kf_upper);
    return mp_form_factor->evaluate(new_ki, new_kf_bin, alpha_f_bin);
}

#endif // FORMFACTORDECORATORROTATION_H


