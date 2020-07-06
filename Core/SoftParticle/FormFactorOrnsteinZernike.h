// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/SoftParticle/FormFactorOrnsteinZernike.h
//! @brief     Defines class FormFactorOrnsteinZernike.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FORMFACTORORNSTEINZERNIKE_H
#define FORMFACTORORNSTEINZERNIKE_H

#include "Core/Scattering/IFormFactorBorn.h"

//! The form factor of a Ornstein-Zernike (see doi:10.1038/pj.2010.110).
//! @ingroup softParticle

class BA_CORE_API_ FormFactorOrnsteinZernike : public IFormFactorBorn
{
public:
    FormFactorOrnsteinZernike(double I0, double xi_xy, double xi_z);

    FormFactorOrnsteinZernike* clone() const override final
    {
        return new FormFactorOrnsteinZernike(m_I0, m_xi_xy, m_xi_z);
    }
    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    double radialExtension() const override final { return m_xi_xy; }

    complex_t evaluate_for_q(cvector_t q) const override final;

private:
    double m_I0;
    double m_xi_xy;
    double m_xi_z;
};

#endif // FORMFACTORORNSTEINZERNIKE_H
