// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SizeSpacingCorrelationApproximationStrategy.cpp
//! @brief     Implements class SizeSpacingCorrelationApproximationStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SizeSpacingCorrelationApproximationStrategy.h"
#include "Exceptions.h"
#include "WeightedFormFactor.h"
#include "IFormFactor.h"
#include "InterferenceFunctionRadialParaCrystal.h"
#include "RealParameter.h"
#include "SimulationElement.h"

SizeSpacingCorrelationApproximationStrategy::SizeSpacingCorrelationApproximationStrategy(
    SimulationOptions sim_params, double kappa)
    : IInterferenceFunctionStrategy(sim_params), m_mean_radius(0.0), m_kappa(kappa)
{
}

void SizeSpacingCorrelationApproximationStrategy::init(
    const SafePointerVector<WeightedFormFactor>& weighted_formfactors,
    const IInterferenceFunction &iff)
{
    IInterferenceFunctionStrategy::init(weighted_formfactors, iff);
    if (m_weighted_ffs.size()==0)
        throw Exceptions::ClassInitializationException(
            "No formfactors for Size-Spacing Correlation Approximation.");
    initMeanRadius();
}

//! Returns the total scattering intensity for given kf and
//! for one layer (implied by the given particle form factors).
//! For each IParticle in the layer layout, the precomputed form factor must be provided.
double SizeSpacingCorrelationApproximationStrategy::evaluateForList(
    const SimulationElement& sim_element) const
{
    double qp = sim_element.getMeanQ().magxy();
    double diffuse_intensity = 0.0;
    if (m_total_abundance <= 0.0)
        return 0.0;
    for (size_t i = 0; i < m_weighted_ffs.size(); ++i) {
        complex_t ff = m_ff[i];
        double fraction = m_weighted_ffs[i]->m_abundance / m_total_abundance;
        diffuse_intensity += fraction * std::norm(ff);
    }
    complex_t mcff  = getMeanCharacteristicFF    (qp, m_ff);
    complex_t mcffc = getMeanConjCharacteristicFF(qp, m_ff);
    complex_t p2kappa = getCharacteristicSizeCoupling(qp, 2.0 * m_kappa);
    complex_t omega = getCharacteristicDistribution(qp);
    double interference_intensity = 2.0 * (mcff * mcffc * omega / (1.0 - p2kappa * omega)).real();
    return m_total_abundance * (diffuse_intensity + interference_intensity);
}

//! Returns the total scattering intensity for given kf and
//! for one layer (implied by the given particle form factors).
//! For each IParticle in the layer layout, the precomputed form factor must be provided.
//! This is the polarized variant of evaluateForList. Each form factor must be
//! precomputed for polarized beam and detector.
double SizeSpacingCorrelationApproximationStrategy::evaluateForMatrixList(
    const SimulationElement& sim_element) const
{
    double qp = sim_element.getMeanQ().magxy();
    Eigen::Matrix2cd diffuse_matrix = Eigen::Matrix2cd::Zero();
    if (m_total_abundance <= 0.0)
        return 0.0;
    for (size_t i = 0; i < m_weighted_ffs.size(); ++i) {
        Eigen::Matrix2cd ff = m_ff_pol[i];
        double fraction = m_weighted_ffs[i]->m_abundance / m_total_abundance;
        diffuse_matrix += fraction * (ff * sim_element.getPolarization() * ff.adjoint());
    }
    Eigen::Matrix2cd mcff  = getMeanCharacteristicMatrixFF    (sim_element.getMeanQ(), m_ff_pol);
    Eigen::Matrix2cd mcffc = getMeanConjCharacteristicMatrixFF(sim_element.getMeanQ(), m_ff_pol);
    complex_t p2kappa = getCharacteristicSizeCoupling(qp, 2.0 * m_kappa);
    complex_t omega = getCharacteristicDistribution(qp);
    Eigen::Matrix2cd interference_matrix
        = (2.0 * omega / (1.0 - p2kappa * omega))
          * (sim_element.getAnalyzerOperator() * mcff * sim_element.getPolarization() * mcffc);
    Eigen::Matrix2cd diffuse_matrix2 = sim_element.getAnalyzerOperator() * diffuse_matrix;
    double interference_trace = std::abs(interference_matrix.trace());
    double diffuse_trace = std::abs(diffuse_matrix2.trace());
    return m_total_abundance * (diffuse_trace + interference_trace);
}

complex_t SizeSpacingCorrelationApproximationStrategy::getMeanCharacteristicFF(
    double qp, const std::vector<complex_t> &ff_list) const
{
    complex_t result(0.0, 0.0);
    for (size_t i = 0; i < m_weighted_ffs.size(); ++i)
        result += m_weighted_ffs[i]->m_abundance * ff_list[i]
                  * calculatePositionOffsetPhase(qp, m_kappa, i);
    return result / m_total_abundance;
}

complex_t SizeSpacingCorrelationApproximationStrategy::getMeanConjCharacteristicFF(
    double qp, const std::vector<complex_t>& ff_list) const
{
    complex_t result(0.0, 0.0);
    for (size_t i = 0; i < m_weighted_ffs.size(); ++i)
        result += m_weighted_ffs[i]->m_abundance * std::conj(ff_list[i])
                  * calculatePositionOffsetPhase(qp, m_kappa, i);
    return result / m_total_abundance;
}

Eigen::Matrix2cd SizeSpacingCorrelationApproximationStrategy::getMeanCharacteristicMatrixFF(
    const kvector_t q, const matrixFFVector_t& ff_list) const
{
    double qp = q.magxy();
    Eigen::Matrix2cd result = Eigen::Matrix2cd::Zero();
    for (size_t i = 0; i < m_weighted_ffs.size(); ++i)
        result += m_weighted_ffs[i]->m_abundance * calculatePositionOffsetPhase(qp, m_kappa, i)
                  * ff_list[i];
    return result / m_total_abundance;
}

Eigen::Matrix2cd SizeSpacingCorrelationApproximationStrategy::getMeanConjCharacteristicMatrixFF(
    const kvector_t q, const matrixFFVector_t& ff_list) const
{
    double qp = q.magxy();
    Eigen::Matrix2cd result = Eigen::Matrix2cd::Zero();
    for (size_t i = 0; i < m_weighted_ffs.size(); ++i)
        result += m_weighted_ffs[i]->m_abundance * calculatePositionOffsetPhase(qp, m_kappa, i)
                  * ff_list[i].adjoint();
    return result / m_total_abundance;
}

complex_t SizeSpacingCorrelationApproximationStrategy::getCharacteristicDistribution(
    double qp) const
{
    const InterferenceFunctionRadialParaCrystal *p_iff
        = dynamic_cast<const InterferenceFunctionRadialParaCrystal*>(mP_iff.get());
    if (p_iff == 0)
        throw Exceptions::ClassInitializationException("Wrong interference function for SSCA");
    return p_iff->FTPDF(qp);
}

complex_t SizeSpacingCorrelationApproximationStrategy::getCharacteristicSizeCoupling(
    double qp, double kappa) const
{
    size_t n_frs = m_weighted_ffs.size();
    complex_t result = complex_t(0.0, 0.0);
    for (size_t i = 0; i < n_frs; ++i)
        result += m_weighted_ffs[i]->m_abundance * calculatePositionOffsetPhase(qp, kappa, i);
    return result / m_total_abundance;
}

complex_t SizeSpacingCorrelationApproximationStrategy::calculatePositionOffsetPhase(
    double qp, double kappa, size_t index) const
{
    return exp_I(kappa * qp * (m_weighted_ffs[index]->mp_ff->getRadialExtension() - m_mean_radius));
}

//! Sets m_mean_radius to the weighted arithmetic average of the particle radii.
void SizeSpacingCorrelationApproximationStrategy::initMeanRadius()
{
    m_mean_radius = 0.0;
    for (const auto wff: m_weighted_ffs)
        m_mean_radius += wff->m_abundance * wff->mp_ff->getRadialExtension();
    if (m_total_abundance > 0.0)
        m_mean_radius /= m_total_abundance;
}
