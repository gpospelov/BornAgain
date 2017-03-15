// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SSCAHelper.cpp
//! @brief     Implements classes SSCAHelper.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SSCAHelper.h"
#include "Exceptions.h"
#include "FormFactorCoherentSum.h"
#include "InterferenceFunctionRadialParaCrystal.h"


SSCAHelper::SSCAHelper(double kappa)
    : m_kappa(kappa)
    , m_mean_radius {}
{}

void SSCAHelper::init(const SafePointerVector<FormFactorCoherentSum>& ff_wrappers)
{
    m_mean_radius = 0.0;
    for (const auto ffw: ff_wrappers)
        m_mean_radius += ffw->relativeAbundance() * ffw->radialExtension();
}

complex_t SSCAHelper::getCharacteristicSizeCoupling(double qp,
        const SafePointerVector<FormFactorCoherentSum>& ff_wrappers) const
{
    complex_t result {};
    for (auto ffw : ff_wrappers)
    {
        double radial_extension = ffw->radialExtension();
        result += ffw->relativeAbundance() *
                  calculatePositionOffsetPhase(2.0*qp, radial_extension);
    }
    return result;
}

complex_t SSCAHelper::getCharacteristicDistribution(
        double qp, const IInterferenceFunction* p_iff) const
{
    const InterferenceFunctionRadialParaCrystal *p_iff_radial
        = dynamic_cast<const InterferenceFunctionRadialParaCrystal*>(p_iff);
    if (p_iff_radial == 0)
        throw Exceptions::ClassInitializationException("Wrong interference function for SSCA");
    return p_iff_radial->FTPDF(qp);
}

complex_t SSCAHelper::calculatePositionOffsetPhase(double qp, double radial_extension) const
{
    return exp_I(m_kappa * qp * (radial_extension - m_mean_radius));
}
