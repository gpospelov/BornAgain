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

template <class T> class IntegratorReal;

//! Percus-Yevick hard disk interference function.
//! @ingroup interference

class BA_CORE_API_ InterferenceFunctionHardDisk : public IInterferenceFunction
{
public:
    InterferenceFunctionHardDisk(double radius, double density);
    ~InterferenceFunctionHardDisk() final;

    InterferenceFunctionHardDisk* clone() const override final;

    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    double getParticleDensity() const override final;

private:
    InterferenceFunctionHardDisk(const InterferenceFunctionHardDisk& other);
    double iff_without_dw(const kvector_t q) const override final;
    void init_parameters();
    void validateParameters() const;
    double packingRatio() const;
    double c_zero(double packing) const;
    double s2(double packing) const;
    double w2(double x) const;
    double integrand(double x) const;
    double m_radius;
    double m_density;
    mutable double m_q, m_c_zero, m_s2, m_packing;
#ifndef SWIG
    std::unique_ptr<IntegratorReal<InterferenceFunctionHardDisk>> mP_integrator;
#endif
};

#endif // INTERFERENCEFUNCTIONHARDDISK_H
