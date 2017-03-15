// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SSCApproximationStrategy.cpp
//! @brief     Implements classes SSCApproximationStrategy1, SSCApproximationStrategy2.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SSCApproximationStrategy.h"
#include "FormFactorCoherentSum.h"
#include "SimulationElement.h"


// ************************************************************************** //
//  class SSCApproximationStrategy1
// ************************************************************************** //

SSCApproximationStrategy1::SSCApproximationStrategy1(SimulationOptions sim_params, double kappa)
    : IInterferenceFunctionStrategy(sim_params)
    , m_helper(kappa)
{}

void SSCApproximationStrategy1::strategy_specific_post_init()
{
    m_helper.init(m_formfactor_wrappers);
}

//! Returns the total scattering intensity for given kf and
//! for one particle layout (implied by the given particle form factors).
//! For each IParticle in the layout, the precomputed form factor must be provided.
double SSCApproximationStrategy1::evaluateForList(const SimulationElement& sim_element) const
{
    double qp = sim_element.getMeanQ().magxy();
    double diffuse_intensity = 0.0;
    auto precomputed_ff = precomputeScalar(sim_element, m_formfactor_wrappers);
    for (size_t i = 0; i < m_formfactor_wrappers.size(); ++i) {
        complex_t ff = precomputed_ff[i];
        double fraction = m_formfactor_wrappers[i]->relativeAbundance();
        diffuse_intensity += fraction * std::norm(ff);
    }
    complex_t mean_ff_norm  = getMeanFormfactorNorm(qp, precomputed_ff);
    complex_t p2kappa = m_helper.getCharacteristicSizeCoupling(qp, m_formfactor_wrappers);
    complex_t omega = m_helper.getCharacteristicDistribution(qp, mP_iff.get());
    double interference_intensity = 2.0 * (mean_ff_norm * omega / (1.0 - p2kappa * omega)).real();
    return diffuse_intensity + interference_intensity;
}

complex_t SSCApproximationStrategy1::getMeanFormfactorNorm(
        double qp, const std::vector<complex_t>& precomputed_ff) const
{
    complex_t ff_orig=0., ff_conj=0.; // original and conjugated mean formfactor
    for (size_t i = 0; i < m_formfactor_wrappers.size(); ++i) {
        double radial_extension = m_formfactor_wrappers[i]->radialExtension();
        complex_t prefac = m_formfactor_wrappers[i]->relativeAbundance()
            * m_helper.calculatePositionOffsetPhase(qp, radial_extension);
        ff_orig += prefac * precomputed_ff[i];
        ff_conj += prefac * std::conj(precomputed_ff[i]);
    }
    return ff_orig * ff_conj;
}

// ************************************************************************** //
//  class SSCApproximationStrategy2
// ************************************************************************** //

SSCApproximationStrategy2::SSCApproximationStrategy2(SimulationOptions sim_params, double kappa)
    : IInterferenceFunctionStrategy(sim_params)
    , m_helper(kappa)
{}

void SSCApproximationStrategy2::strategy_specific_post_init()
{
    m_helper.init(m_formfactor_wrappers);
}

//! Returns the total scattering intensity for given kf and
//! for one layer (implied by the given particle form factors).
//! For each IParticle in the layer layout, the precomputed form factor must be provided.
//! This is the polarized variant of evaluateForList. Each form factor must be
//! precomputed for polarized beam and detector.
double SSCApproximationStrategy2::evaluateForList(const SimulationElement& sim_element) const
{
    double qp = sim_element.getMeanQ().magxy();
    Eigen::Matrix2cd diffuse_matrix = Eigen::Matrix2cd::Zero();
    auto precomputed_ff = precomputePolarized(sim_element, m_formfactor_wrappers);
    for (size_t i = 0; i < m_formfactor_wrappers.size(); ++i) {
        Eigen::Matrix2cd ff = precomputed_ff[i];
        double fraction = m_formfactor_wrappers[i]->relativeAbundance();
        diffuse_matrix += fraction * (ff * sim_element.getPolarization() * ff.adjoint());
    }
    Eigen::Matrix2cd mff_orig, mff_conj; // original and conjugated mean formfactor
    getMeanFormfactors(qp, mff_orig, mff_conj, precomputed_ff);
    complex_t p2kappa = m_helper.getCharacteristicSizeCoupling(qp, m_formfactor_wrappers);
    complex_t omega = m_helper.getCharacteristicDistribution(qp, mP_iff.get());
    Eigen::Matrix2cd interference_matrix
        = (2.0 * omega / (1.0 - p2kappa * omega))
        * sim_element.getAnalyzerOperator() * mff_orig
        * sim_element.getPolarization() * mff_conj;
    Eigen::Matrix2cd diffuse_matrix2 = sim_element.getAnalyzerOperator() * diffuse_matrix;
    double interference_trace = std::abs(interference_matrix.trace());
    double diffuse_trace = std::abs(diffuse_matrix2.trace());
    return diffuse_trace + interference_trace;
}

//! Computes ff_orig and ff_conj.
void SSCApproximationStrategy2::getMeanFormfactors(
    double qp, Eigen::Matrix2cd& ff_orig, Eigen::Matrix2cd& ff_conj,
    const matrixFFVector_t& precomputed_ff) const
{
    ff_orig=Eigen::Matrix2cd::Zero();
    ff_conj=Eigen::Matrix2cd::Zero();
    for (size_t i = 0; i < m_formfactor_wrappers.size(); ++i) {
        double radial_extension = m_formfactor_wrappers[i]->radialExtension();
        complex_t prefac = m_formfactor_wrappers[i]->relativeAbundance()
            * m_helper.calculatePositionOffsetPhase(qp, radial_extension);
        ff_orig += prefac * precomputed_ff[i];
        ff_conj += prefac * precomputed_ff[i].adjoint();
    }
}
