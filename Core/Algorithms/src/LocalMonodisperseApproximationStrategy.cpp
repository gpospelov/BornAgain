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

double LocalMonodisperseApproximationStrategy::evaluateForComplexkz(
        kvector_t k_i, kvector_t k_f, complex_t k_iz, complex_t k_fz) const
{
    double intensity = 0.0;
    for (size_t i=0; i<m_form_factors.size(); ++i) {
        complex_t ff = m_form_factors[i]->evaluateForComplexkz(k_i, k_f, k_iz, k_fz);
        double itf_function = m_interference_functions[i]->evaluate(k_i-k_f);
        double fraction = m_fractions[i];
        intensity += fraction*itf_function*std::norm(ff);
    }
    return intensity;
}

bool LocalMonodisperseApproximationStrategy::checkVectorSizes()
{
    size_t n_ffs = m_form_factors.size();
    size_t n_frs = m_fractions.size();
    size_t n_ifs = m_interference_functions.size();
    return (n_ffs==n_frs && n_ifs==n_ffs);
}
