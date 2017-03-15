// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SSCAHelper.h
//! @brief     Defines classes SSCAHelper.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SSCAHELPER_H
#define SSCAHELPER_H

#include "Complex.h"
#include "SafePointerVector.h"

class FormFactorCoherentSum;
class IInterferenceFunction;

//! Helper class for SSCApproximationStrategy, offering some methods, shared between
//! the scalar and polarized scattering calculations
//! @ingroup algorithms_internal

class SSCAHelper
{
public:
    SSCAHelper(double kappa);

    void init(const SafePointerVector<FormFactorCoherentSum>& ff_wrappers);

    complex_t getCharacteristicSizeCoupling(double qp,
            const SafePointerVector<FormFactorCoherentSum>& ff_wrappers) const;
    complex_t getCharacteristicDistribution(double qp, const IInterferenceFunction* p_iff) const;
    complex_t calculatePositionOffsetPhase(double qp, double radial_extension) const;

private:
    double m_kappa;
    double m_mean_radius;
};

#endif // SSCAHELPER_H
