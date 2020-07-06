// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/SoftParticle/FormFactorDebyeBueche.h
//! @brief     Defines class FormFactorDebyeBueche.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_SOFTPARTICLE_FORMFACTORDEBYEBUECHE_H
#define BORNAGAIN_CORE_SOFTPARTICLE_FORMFACTORDEBYEBUECHE_H

#include "Core/Scattering/IFormFactorBorn.h"

//! The form factor of a Debye-Bueche (see doi:10.1038/pj.2010.110).
//! @ingroup softParticle

class BA_CORE_API_ FormFactorDebyeBueche : public IFormFactorBorn
{
public:
    FormFactorDebyeBueche(double I0, double xi);

    FormFactorDebyeBueche* clone() const override final
    {
        return new FormFactorDebyeBueche(m_I0, m_xi);
    }
    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    double radialExtension() const override final { return m_xi; }

    complex_t evaluate_for_q(cvector_t q) const override final;

private:
    double m_I0;
    double m_xi;
};

#endif // BORNAGAIN_CORE_SOFTPARTICLE_FORMFACTORDEBYEBUECHE_H
