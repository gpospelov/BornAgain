// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Interference/SSCApproximationStrategy.cpp
//! @brief     Implements class SSCApproximationStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Sample/Interference/SSCApproximationStrategy.h"
#include "Base/Pixel/SimulationElement.h"
#include "Sample/Aggregate/IInterferenceFunction.h"
#include "Sample/Fresnel/FormFactorCoherentSum.h"

SSCApproximationStrategy::SSCApproximationStrategy(
    const std::vector<FormFactorCoherentSum>& weighted_formfactors,
    const IInterferenceFunction* p_iff, SimulationOptions sim_params, bool polarized, double kappa)
    : IInterferenceFunctionStrategy(weighted_formfactors, p_iff, sim_params, polarized)
    , m_helper(kappa)
{
    m_helper.init(m_formfactor_wrappers);
}

//! Returns the total scattering intensity for given kf and
//! for one particle layout (implied by the given particle form factors).
//! This is the scalar version
double SSCApproximationStrategy::scalarCalculation(const SimulationElement& sim_element) const
{
    double qp = sim_element.getMeanQ().magxy();
    double diffuse_intensity = 0.0;
    complex_t ff_orig = 0., ff_conj = 0.; // original and conjugated mean formfactor
    for (auto& ffw : m_formfactor_wrappers) {
        complex_t ff = ffw.evaluate(sim_element);
        double fraction = ffw.relativeAbundance();
        diffuse_intensity += fraction * std::norm(ff);
        double radial_extension = ffw.radialExtension();
        complex_t prefac =
            ffw.relativeAbundance() * m_helper.calculatePositionOffsetPhase(qp, radial_extension);
        ff_orig += prefac * ff;
        ff_conj += prefac * std::conj(ff);
    }
    complex_t mean_ff_norm = ff_orig * ff_conj;
    complex_t p2kappa = m_helper.getCharacteristicSizeCoupling(qp, m_formfactor_wrappers);
    complex_t omega = m_helper.getCharacteristicDistribution(qp, m_iff.get());
    double iff = 2.0 * (mean_ff_norm * omega / (1.0 - p2kappa * omega)).real();
    double dw_factor = m_iff->DWfactor(sim_element.getMeanQ());
    return diffuse_intensity + dw_factor * iff;
}

//! This is the polarized version
double SSCApproximationStrategy::polarizedCalculation(const SimulationElement& sim_element) const
{
    double qp = sim_element.getMeanQ().magxy();
    Eigen::Matrix2cd diffuse_matrix = Eigen::Matrix2cd::Zero();
    const auto& polarization_handler = sim_element.polarizationHandler();
    Eigen::Matrix2cd ff_orig = Eigen::Matrix2cd::Zero();
    Eigen::Matrix2cd ff_conj = Eigen::Matrix2cd::Zero();
    for (auto& ffw : m_formfactor_wrappers) {
        Eigen::Matrix2cd ff = ffw.evaluatePol(sim_element);
        double fraction = ffw.relativeAbundance();
        diffuse_matrix += fraction * (ff * polarization_handler.getPolarization() * ff.adjoint());
        double radial_extension = ffw.radialExtension();
        complex_t prefac =
            ffw.relativeAbundance() * m_helper.calculatePositionOffsetPhase(qp, radial_extension);
        ff_orig += prefac * ff;
        ff_conj += prefac * ff.adjoint();
    }
    complex_t p2kappa = m_helper.getCharacteristicSizeCoupling(qp, m_formfactor_wrappers);
    complex_t omega = m_helper.getCharacteristicDistribution(qp, m_iff.get());
    Eigen::Matrix2cd interference_matrix = (2.0 * omega / (1.0 - p2kappa * omega))
                                           * polarization_handler.getAnalyzerOperator() * ff_orig
                                           * polarization_handler.getPolarization() * ff_conj;
    Eigen::Matrix2cd diffuse_matrix2 = polarization_handler.getAnalyzerOperator() * diffuse_matrix;
    double interference_trace = std::abs(interference_matrix.trace());
    double diffuse_trace = std::abs(diffuse_matrix2.trace());
    double dw_factor = m_iff->DWfactor(sim_element.getMeanQ());
    return diffuse_trace + dw_factor * interference_trace;
}
