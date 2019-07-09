// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/SLDProfile.cpp
//! @brief     Implements class SLDProfile.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "SLDProfile.h"
#include "LayerRoughness.h"
#include "ProcessedSample.h"

namespace {
const double prefactor = std::sqrt(2.0/M_PI);
double Transition(double x, double sigma);
double TransitionTanh(double x);
}

SLDProfile::SLDProfile(const ProcessedSample& sample)
{
    auto N = sample.numberOfSlices();
    m_materials.reserve(N);
    if (N>1) {
        m_zlimits.reserve(N-1);
        m_sigmas.reserve(N-1);
    }
    auto& slices = sample.slices();
    for (size_t i=0; i<N; ++i) {
        m_materials.push_back(slices[i].material());
        if (i+1 < N) {
            m_zlimits.push_back(sample.sliceBottomZ(i));
            if (auto p_roughness = sample.bottomRoughness(i)) {
                m_sigmas.push_back(p_roughness->getSigma());
            } else {
                m_sigmas.push_back(0.0);
            }
        }
    }
}

complex_t SLDProfile::sld(double z, const std::vector<complex_t>& slds) const
{
    if (slds.size() == 0) return 0.0;
    complex_t result = slds[0];
    for (size_t i = 0; i<m_zlimits.size(); ++i) {
        auto sld_diff = slds[i+1] - slds[i];
        auto arg = (z - m_zlimits[i]);
        auto t = Transition(arg, m_sigmas[i]);
        result += sld_diff * t;
    }
    return result;
}

SLDProfile::~SLDProfile() = default;

namespace {
double Transition(double x, double sigma)
{
    if (sigma <= 0.0)
        return x < 0.0 ? 1.0 : 0.0;
    return TransitionTanh(x/sigma);
}
double TransitionTanh(double x) {
    return (1.0 - std::tanh(prefactor*x))/2.0;
}
}
