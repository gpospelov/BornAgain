// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Interference/DecouplingApproximationStrategy.cpp
//! @brief     Implements class DecouplingApproximationStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Sample/Interference/DecouplingApproximationStrategy.h"
#include "Base/Pixel/SimulationElement.h"
#include "Base/Types/Exceptions.h"
#include "Base/Utils/MathFunctions.h"
#include "Param/Base/RealParameter.h"
#include "Sample/Aggregate/IInterferenceFunction.h"
#include "Sample/Fresnel/FormFactorCoherentSum.h"

DecouplingApproximationStrategy::DecouplingApproximationStrategy(
    const std::vector<FormFactorCoherentSum>& weighted_formfactors,
    const IInterferenceFunction* iff, SimulationOptions sim_params, bool polarized)
    : IInterferenceFunctionStrategy(weighted_formfactors, iff, sim_params, polarized)
{
}

//! Returns the total incoherent and coherent scattering intensity for given kf and
//! for one particle layout (implied by the given particle form factors).
//! This is the scalar version
double
DecouplingApproximationStrategy::scalarCalculation(const SimulationElement& sim_element) const
{
    double intensity = 0.0;
    complex_t amplitude = complex_t(0.0, 0.0);
    for (auto& ffw : m_weighted_formfactors) {
        complex_t ff = ffw.evaluate(sim_element);
        if (std::isnan(ff.real()))
            throw Exceptions::RuntimeErrorException(
                "DecouplingApproximationStrategy::scalarCalculation() -> Error! Amplitude is NaN");
        double fraction = ffw.relativeAbundance();
        amplitude += fraction * ff;
        intensity += fraction * std::norm(ff);
    }
    double amplitude_norm = std::norm(amplitude);
    double coherence_factor = m_iff->evaluate(sim_element.meanQ());
    return intensity + amplitude_norm * (coherence_factor - 1.0);
}

//! This is the polarized version
double
DecouplingApproximationStrategy::polarizedCalculation(const SimulationElement& sim_element) const
{
    Eigen::Matrix2cd mean_intensity = Eigen::Matrix2cd::Zero();
    Eigen::Matrix2cd mean_amplitude = Eigen::Matrix2cd::Zero();

    const auto& polarization_handler = sim_element.polarizationHandler();
    for (auto& ffw : m_weighted_formfactors) {
        Eigen::Matrix2cd ff = ffw.evaluatePol(sim_element);
        if (!ff.allFinite())
            throw Exceptions::RuntimeErrorException(
                "DecouplingApproximationStrategy::polarizedCalculation() -> "
                "Error! Form factor contains NaN or infinite");
        double fraction = ffw.relativeAbundance();
        mean_amplitude += fraction * ff;
        mean_intensity += fraction * (ff * polarization_handler.getPolarization() * ff.adjoint());
    }
    Eigen::Matrix2cd amplitude_matrix = polarization_handler.getAnalyzerOperator() * mean_amplitude
                                        * polarization_handler.getPolarization()
                                        * mean_amplitude.adjoint();
    Eigen::Matrix2cd intensity_matrix = polarization_handler.getAnalyzerOperator() * mean_intensity;
    double amplitude_trace = std::abs(amplitude_matrix.trace());
    double intensity_trace = std::abs(intensity_matrix.trace());
    double coherence_factor = m_iff->evaluate(sim_element.meanQ());
    return intensity_trace + amplitude_trace * (coherence_factor - 1.0);
}
