#include "SizeSpacingCorrelationApproximationStrategy.h"
#include "InterferenceFunction1DParaCrystal.h"

SizeSpacingCorrelationApproximationStrategy::SizeSpacingCorrelationApproximationStrategy(
        double kappa)
: m_mean_radius(0.0)
, m_kappa(kappa)
{
}

void SizeSpacingCorrelationApproximationStrategy::init(
        const std::vector<IFormFactor*>& form_factors,
        const std::vector<double>& fractions,
        const std::vector<IInterferenceFunction*>& interference_functions)
{
    IInterferenceFunctionStrategy::init(form_factors, fractions, interference_functions);
    if (!checkVectorSizes()) {
        throw ClassInitializationException("Wrong number of formfactors or interference functions for Decoupling Approximation.");
    }
    initMeanRadius();
}

double SizeSpacingCorrelationApproximationStrategy::evaluate(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin, double alpha_i, double alpha_f) const
{
    double qp = getqp(k_i, k_f_bin);
    double diffuse_intensity = 0.0;
    for (size_t i=0; i<m_form_factors.size(); ++i) {
        complex_t ff = m_form_factors[i]->evaluate(k_i, k_f_bin, alpha_i, alpha_f);
        double fraction = m_fractions[i];
        diffuse_intensity += fraction*(std::norm(ff));
    }
    complex_t mcff = getMeanCharacteristicFF(k_i, k_f_bin, alpha_i, alpha_f);
    complex_t mcffc = getMeanConjCharacteristicFF(k_i, k_f_bin, alpha_i, alpha_f);
    complex_t p2kappa = getCharacteristicSizeCoupling(qp, 2.0*m_kappa);
    complex_t omega = getCharacteristicDistribution(qp);
    double interference_intensity = 2.0*( mcff*mcffc*omega/(1.0 - p2kappa*omega) ).real();
    return diffuse_intensity + interference_intensity;
}

bool SizeSpacingCorrelationApproximationStrategy::checkVectorSizes() const
{
    size_t n_ffs = m_form_factors.size();
    size_t n_frs = m_fractions.size();
    size_t n_ifs = m_ifs.size();
    return (n_ffs==n_frs && n_ifs==1);
}

complex_t SizeSpacingCorrelationApproximationStrategy::getMeanCharacteristicFF(
        const cvector_t& k_i, const Bin1DCVector& k_f_bin, double alpha_i,
        double alpha_f) const
{
    double qp = getqp(k_i, k_f_bin);
    complex_t result(0.0, 0.0);
    for (size_t i=0; i<m_form_factors.size(); ++i) {
        result += m_fractions[i]*m_form_factors[i]->evaluate(k_i, k_f_bin, alpha_i, alpha_f)*
                calculatePositionOffsetPhase(qp, m_kappa, i);
    }
    return result;
}

complex_t SizeSpacingCorrelationApproximationStrategy::getMeanConjCharacteristicFF(
        const cvector_t& k_i, const Bin1DCVector& k_f_bin, double alpha_i,
        double alpha_f) const
{
    double qp = getqp(k_i, k_f_bin);
    complex_t result(0.0, 0.0);
    for (size_t i=0; i<m_form_factors.size(); ++i) {
        result += m_fractions[i]*std::conj(m_form_factors[i]->evaluate(k_i, k_f_bin, alpha_i, alpha_f))*
                calculatePositionOffsetPhase(qp, m_kappa, i);
    }
    return result;
}

complex_t SizeSpacingCorrelationApproximationStrategy::getCharacteristicDistribution(
        double qp) const
{
    const InterferenceFunction1DParaCrystal *p_iff = dynamic_cast<const InterferenceFunction1DParaCrystal *>(
            m_ifs[0]);
    if (p_iff==0) {
        throw ClassInitializationException("Wrong interference function for SSCA");
    }
    return p_iff->FTGaussianCorrLength(qp);
}

complex_t SizeSpacingCorrelationApproximationStrategy::getCharacteristicSizeCoupling(
        double qp, double kappa) const
{
    size_t n_frs = m_fractions.size();
    complex_t result = complex_t(0.0, 0.0);
    for (size_t i=0; i<n_frs; ++i) {
        result += m_fractions[i]* calculatePositionOffsetPhase(qp, kappa, i);
    }
    return result;
}

complex_t SizeSpacingCorrelationApproximationStrategy::calculatePositionOffsetPhase(
        double qp, double kappa, size_t index) const
{
    return std::exp(complex_t(0.0, 1.0)*kappa*qp*(m_form_factors[index]->getRadius()-m_mean_radius));
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
    for (size_t i=0; i<m_form_factors.size(); ++i) {
        m_mean_radius += m_fractions[i]*m_form_factors[i]->getRadius();
    }
}
