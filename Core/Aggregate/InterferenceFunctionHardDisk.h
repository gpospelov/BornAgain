// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/InterferenceFunctionHardDisk.h
//! @brief     Defines class InterferenceFunctionHardDisk.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef INTERFERENCEFUNCTIONHARDDISK_H
#define INTERFERENCEFUNCTIONHARDDISK_H

#include "IInterferenceFunction.h"
#include "Integrator.h"

//! Percus-Yevick hard disk interference function.
//!
//! M.S. Ripoll & C.F. Tejero (1995) Approximate analytical expression for the direct correlation
//! function of hard discs within the Percus-Yevick equation, Molecular Physics, 85:2, 423-428,
//! DOI: 10.1080/00268979500101211
//! @ingroup interference

class BA_CORE_API_ InterferenceFunctionHardDisk : public IInterferenceFunction
{
public:
    InterferenceFunctionHardDisk(double radius, double density);
    ~InterferenceFunctionHardDisk() final;

    InterferenceFunctionHardDisk* clone() const override final;

    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    double getParticleDensity() const override final;

    double radius() const;
    double density() const;

private:
    InterferenceFunctionHardDisk(const InterferenceFunctionHardDisk& other);
    double iff_without_dw(const kvector_t q) const override final;
    void init_parameters();
    void validateParameters() const;
    double packingRatio() const;
    double integrand(double x) const;
    double m_radius;
    double m_density;
    mutable double m_q, m_c_zero, m_s2, m_packing;
    mutable RealIntegrator m_integrator;
};

#endif // INTERFERENCEFUNCTIONHARDDISK_H
