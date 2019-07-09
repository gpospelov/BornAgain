// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/ProfileHelper.cpp
//! @brief     Implements class ProfileHelper.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "ProfileHelper.h"
#include "LayerRoughness.h"
#include "ProcessedSample.h"

namespace
{
const double prefactor = std::sqrt(2.0 / M_PI);
double Transition(double x, double sigma);
double TransitionTanh(double x);
} // namespace

ProfileHelper::ProfileHelper(const ProcessedSample& sample)
{
    auto N = sample.numberOfSlices();
    m_materialdata.reserve(N);
    if (N > 1) {
        m_zlimits.reserve(N - 1);
        m_sigmas.reserve(N - 1);
    }
    auto& slices = sample.averageSlices();
    for (size_t i = 0; i < N; ++i) {
        m_materialdata.push_back(slices[i].material().materialData());
        if (i + 1 < N) {
            m_zlimits.push_back(sample.sliceBottomZ(i));
            if (auto p_roughness = sample.bottomRoughness(i)) {
                m_sigmas.push_back(p_roughness->getSigma());
            } else {
                m_sigmas.push_back(0.0);
            }
        }
    }
}

std::vector<complex_t> ProfileHelper::calculateProfile(const std::vector<double>& z_values) const
{
    complex_t top_value = m_materialdata.size() ? m_materialdata[0] : 0.0;
    std::vector<complex_t> result(z_values.size(), top_value);
    for (size_t i = 0; i < m_zlimits.size(); ++i) {
        auto sld_diff = m_materialdata[i + 1] - m_materialdata[i];
        for (size_t j = 0; j < z_values.size(); ++j) {
            auto arg = (z_values[j] - m_zlimits[i]);
            auto t = Transition(arg, m_sigmas[i]);
            result[j] += sld_diff * t;
        }
    }
    return result;
}

ProfileHelper::~ProfileHelper() = default;

namespace
{
double Transition(double x, double sigma)
{
    if (sigma <= 0.0)
        return x < 0.0 ? 1.0 : 0.0;
    return TransitionTanh(x / sigma);
}
double TransitionTanh(double x)
{
    return (1.0 - std::tanh(prefactor * x)) / 2.0;
}
} // namespace
