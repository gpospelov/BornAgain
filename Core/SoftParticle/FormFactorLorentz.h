// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/SoftParticle/FormFactorLorentz.h
//! @brief     Defines class FormFactorLorentz.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FORMFACTORLORENTZ_H
#define FORMFACTORLORENTZ_H

#include "Core/Scattering/IFormFactorBorn.h"

//! The form factor of a lorentzian.
//! @ingroup softParticle

class BA_CORE_API_ FormFactorLorentz : public IFormFactorBorn
{
public:
    FormFactorLorentz(double length);
    FormFactorLorentz(double width, double height);

    FormFactorLorentz* clone() const override final
    {
        return new FormFactorLorentz(m_width, m_height);
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

#endif // FORMFACTORLORENTZ_H
