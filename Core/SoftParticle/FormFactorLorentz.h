// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/SoftParticle/FormFactorLorentz.h
//! @brief     Defines class FormFactorLorentzSphere.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_SOFTPARTICLE_FORMFACTORLORENTZ_H
#define BORNAGAIN_CORE_SOFTPARTICLE_FORMFACTORLORENTZ_H

#include "Core/Scattering/IFormFactorBorn.h"

//! The form factor of a lorentzian.
//! @ingroup softParticle

class BA_CORE_API_ FormFactorLorentzSphere : public IFormFactorBorn
{
public:
    FormFactorLorentzSphere(double length);
    FormFactorLorentzSphere(double width, double height);

    FormFactorLorentzSphere* clone() const override final
    {
        return new FormFactorLorentzSphere(m_width, m_height);
    }
    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    double getWidth() const { return m_width; }
    double getHeight() const { return m_height; }

    double radialExtension() const override final;

    complex_t evaluate_for_q(cvector_t q) const override final;

protected:
    void onChange() override final;

private:
    double m_width;
    double m_height;
    void initialize();
};

#endif // BORNAGAIN_CORE_SOFTPARTICLE_FORMFACTORLORENTZ_H
