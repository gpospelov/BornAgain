// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/SizeSpacingCorrelationApproximationStrategy.cpp
//! @brief     Implements class SizeSpacingCorrelationApproximationStrategy.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SizeSpacingCorrelationApproximationStrategy.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "MathFunctions.h"

SizeSpacingCorrelationApproximationStrategy::SizeSpacingCorrelationApproximationStrategy(
        SimulationParameters sim_params, double kappa)
: IInterferenceFunctionStrategy(sim_params)
, m_mean_radius(0.0)
, m_kappa(kappa)
{
}

void SizeSpacingCorrelationApproximationStrategy::init(
        const SafePointerVector<FormFactorInfo>& form_factor_infos,
        const SafePointerVector<IInterferenceFunction>& ifs)
{
    IInterferenceFunctionStrategy::init(form_factor_infos, ifs);
    if (!checkVectorSizes()) {
        throw ClassInitializationException("Wrong number of formfactors"
                " or interference functions for Size-Spacing Correlation Approximation.");
    }
    initMeanRadius();
}

double SizeSpacingCorrelationApproximationStrategy::evaluateForList(
        const cvector_t& k_i, const Bin1DCVector& k_f_bin,
        const std::vector<complex_t> &ff_list) const
{
    double qp = getqp(k_i, k_f_bin);
    double diffuse_intensity = 0.0;
    for (size_t i=0; i<m_ff_infos.size(); ++i) {
        complex_t ff = ff_list[i];
        double fraction = m_ff_infos[i]->m_abundance;
        diffuse_intensity += fraction*(std::norm(ff));
    }
    complex_t mcff = getMeanCharacteristicFF(k_i, k_f_bin, ff_list);
    complex_t mcffc = getMeanConjCharacteristicFF(k_i, k_f_bin, ff_list);
    complex_t p2kappa = getCharacteristicSizeCoupling(qp, 2.0*m_kappa);
    complex_t omega = getCharacteristicDistribution(qp);
    double interference_intensity = 2.0
            * ( mcff*mcffc*omega/(1.0 - p2kappa*omega) ).real();
    return diffuse_intensity + interference_intensity;
}

bool SizeSpacingCorrelationApproximationStrategy::checkVectorSizes() const
{
    size_t n_ffs = m_ff_infos.size();
    size_t n_ifs = m_ifs.size();
    return (n_ffs>0 && n_ifs==1);
}

complex_t SizeSpacingCorrelationApproximationStrategy::getMeanCharacteristicFF(
        const cvector_t& k_i, const Bin1DCVector& k_f_bin,
        const std::vector<complex_t> &ff_list) const
{
    double qp = getqp(k_i, k_f_bin);
    complex_t result(0.0, 0.0);
    for (size_t i=0; i<m_ff_infos.size(); ++i) {
        result += m_ff_infos[i]->m_abundance * ff_list[i]
                * calculatePositionOffsetPhase(qp, m_kappa, i);
    }
    return result;
}

complex_t
SizeSpacingCorrelationApproximationStrategy::getMeanConjCharacteristicFF(
        const cvector_t& k_i, const Bin1DCVector& k_f_bin,
        const std::vector<complex_t> &ff_list) const
{
    double qp = getqp(k_i, k_f_bin);
    complex_t result(0.0, 0.0);
    for (size_t i=0; i<m_ff_infos.size(); ++i) {
        result += m_ff_infos[i]->m_abundance * std::conj(ff_list[i])
                * calculatePositionOffsetPhase(qp, m_kappa, i);
    }
    return result;
}

complex_t
SizeSpacingCorrelationApproximationStrategy::getCharacteristicDistribution(
        double qp) const
{
    const InterferenceFunction1DParaCrystal *p_iff =
            dynamic_cast<const InterferenceFunction1DParaCrystal *>(m_ifs[0]);
    if (p_iff==0) {
        throw ClassInitializationException("Wrong interference function for SSCA");
    }
    return p_iff->FTGaussianCorrLength(qp);
}

complex_t
SizeSpacingCorrelationApproximationStrategy::getCharacteristicSizeCoupling(
        double qp, double kappa) const
{
    size_t n_frs = m_ff_infos.size();
    complex_t result = complex_t(0.0, 0.0);
    for (size_t i=0; i<n_frs; ++i) {
        result += m_ff_infos[i]->m_abundance
                * calculatePositionOffsetPhase(qp, kappa, i);
    }
    return result;
}

complex_t
SizeSpacingCorrelationApproximationStrategy::calculatePositionOffsetPhase(
        double qp, double kappa, size_t index) const
{
    return std::exp(complex_t(0.0, 1.0) * kappa * qp
            * (m_ff_infos[index]->mp_ff->getRadius()-m_mean_radius));
}

double SizeSpacingCorrelationApproximationStrategy::getqp(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin) const
{
    cvector_t q = k_i - k_f_bin.getMidPoint();
    double qxr = q.x().real();
    double qyr = q.y().real();
    return std::sqrt(qxr*qxr + qyr*qyr);
}

void SizeSpacingCorrelationApproximationStrategy::initMeanRadius()
{
    m_mean_radius = 0.0;
    for (size_t i=0; i<m_ff_infos.size(); ++i) {
        m_mean_radius += m_ff_infos[i]->m_abundance
                       * m_ff_infos[i]->mp_ff->getRadius();
    }
}

