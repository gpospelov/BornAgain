// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorFullSphere.h
//! @brief     Defines class FormFactorFullSphere.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORFULLSPHERE_H
#define FORMFACTORFULLSPHERE_H

#include "IFormFactorBorn.h"

//! A full sphere.
//! @ingroup hardParticle

class BA_CORE_API_ FormFactorFullSphere : public IFormFactorBorn
{
public:
    FormFactorFullSphere(double radius);

    FormFactorFullSphere* clone() const override final {
        return new FormFactorFullSphere(m_radius); }
    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    double getRadius() const { return m_radius; }

    double getRadialExtension() const override final { return m_radius; }

    double bottomZ(const IRotation& rotation) const override final;

    double topZ(const IRotation& rotation) const override final;

    complex_t evaluate_for_q(cvector_t q) const override final;

protected:
    IFormFactor* sliceFormFactor(ZLimits limits, const IRotation& rot,
                                 kvector_t translation) const override final;

    void onChange() override final;

private:
    double m_radius;
};

#endif // FORMFACTORFULLSPHERE_H
