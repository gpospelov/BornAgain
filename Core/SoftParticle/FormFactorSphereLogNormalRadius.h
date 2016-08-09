// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/SoftParticle/FormFactorSphereLogNormalRadius.h
//! @brief     Defines and implements class FormFactorSphereLogNormalRadius.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORSPHERELOGNORMALRADIUS_H
#define FORMFACTORSPHERELOGNORMALRADIUS_H

#include "FormFactorFullSphere.h"
#include "SafePointerVector.h"

class DistributionLogNormal;

//! @class FormFactorSphereLogNormalRadius
//! @ingroup formfactors
//! @brief The formfactor of sphere with log normal radius distribution.

class BA_CORE_API_ FormFactorSphereLogNormalRadius : public IFormFactorBorn
{
public:
    FormFactorSphereLogNormalRadius(double mean, double scale_param, size_t n_samples);
    virtual ~FormFactorSphereLogNormalRadius();

    virtual FormFactorSphereLogNormalRadius *clone() const {
        return new FormFactorSphereLogNormalRadius(m_mean, m_scale_param, m_n_samples); }
    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    virtual double getRadialExtension() const;

    virtual complex_t evaluate_for_q(const cvector_t q) const;

private:
    double m_mean;
    double m_scale_param;
    size_t m_n_samples;

    DistributionLogNormal *mp_distribution;

    SafePointerVector<IFormFactorBorn> m_form_factors;
    std::vector<double> m_probabilities;
};

#endif // FORMFACTORSPHERELOGNORMALRADIUS_H
