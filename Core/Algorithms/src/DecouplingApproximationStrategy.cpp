#include "DecouplingApproximationStrategy.h"
#include "Exceptions.h"

DecouplingApproximationStrategy::DecouplingApproximationStrategy()
{
}

void DecouplingApproximationStrategy::init(
        const std::vector<IFormFactor*>& form_factors,
        const std::vector<double>& fractions,
        const std::vector<IInterferenceFunction*>& interference_functions)
{
    IInterferenceFunctionStrategy::init(form_factors, fractions, interference_functions);
    if (!checkVectorSizes()) {
        throw ClassInitializationException("Wrong number of formfactors or interference functions for Decoupling Approximation.");
    }
}

double DecouplingApproximationStrategy::evaluate(cvector_t k_i,
        cvector_t k_f, double alpha_i, double alpha_f) const
{
    double intensity = 0.0;
    complex_t amplitude = complex_t(0.0, 0.0);
    for (size_t i=0; i<m_form_factors.size(); ++i) {
        complex_t ff = m_form_factors[i]->evaluate(k_i, k_f, alpha_i, alpha_f);
        double fraction = m_fractions[i];
        amplitude += fraction*ff;
        intensity += fraction*(std::norm(ff)); // + m_form_factors[i]->evaluateDiffuse(k_i, k_f, alpha_i, alpha_f));
    }
    double amplitude_norm = std::norm(amplitude);
    double itf_function = m_interference_functions[0]->evaluate(k_i-k_f);
    return intensity + amplitude_norm*(itf_function-1.0);
}

bool DecouplingApproximationStrategy::checkVectorSizes()
{
    size_t n_ffs = m_form_factors.size();
    size_t n_frs = m_fractions.size();
    size_t n_ifs = m_interference_functions.size();
    return (n_ffs==n_frs && n_ifs==1);
}

