#include "LocalMonodisperseApproximationStrategy.h"
#include "Exceptions.h"

LocalMonodisperseApproximationStrategy::LocalMonodisperseApproximationStrategy()
{
}

void LocalMonodisperseApproximationStrategy::init(
        const std::vector<IFormFactor*>& form_factors,
        const std::vector<double>& fractions,
        const std::vector<IInterferenceFunction*>& interference_functions)
{
    IInterferenceFunctionStrategy::init(form_factors, fractions, interference_functions);
    if (!checkVectorSizes()) {
        throw ClassInitializationException("Wrong number of formfactors or interference functions for Decoupling Approximation.");
    }
}

double LocalMonodisperseApproximationStrategy::evaluate(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin, double alpha_i, double alpha_f) const
{
    double intensity = 0.0;
    for (size_t i=0; i<m_form_factors.size(); ++i) {
        complex_t ff = m_form_factors[i]->evaluate(k_i, k_f_bin, alpha_i, alpha_f);
        double itf_function = m_ifs[i]->evaluate(k_i-k_f_bin.getMidPoint());
        double fraction = m_fractions[i];
        intensity += fraction*(itf_function*std::norm(ff));
    }
    return intensity;
}

bool LocalMonodisperseApproximationStrategy::checkVectorSizes()
{
    size_t n_ffs = m_form_factors.size();
    size_t n_frs = m_fractions.size();
    size_t n_ifs = m_ifs.size();
    return (n_ffs==n_frs && n_ifs==n_ffs);
}
