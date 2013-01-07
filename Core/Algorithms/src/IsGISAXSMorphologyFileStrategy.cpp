#include "IsGISAXSMorphologyFileStrategy.h"

IsGISAXSMorphologyFileStrategy::IsGISAXSMorphologyFileStrategy()
{
}

void IsGISAXSMorphologyFileStrategy::init(
        const std::vector<IFormFactor*>& form_factors,
        const std::vector<double>& fractions,
        const std::vector<IInterferenceFunction*>& interference_functions)
{
    IInterferenceFunctionStrategy::init(form_factors, fractions, interference_functions);
    if (!checkVectorSizes()) {
        throw ClassInitializationException(
                "Wrong number of formfactors or interference functions for IsGISAXS morphology file strategy.");
    }
}

double IsGISAXSMorphologyFileStrategy::evaluate(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin, double alpha_i, double alpha_f) const
{
}

bool IsGISAXSMorphologyFileStrategy::checkVectorSizes()
{
    size_t n_ffs = m_form_factors.size();
    size_t n_frs = m_fractions.size();
    size_t n_ifs = m_interference_functions.size();
    return (n_ffs==n_frs && n_ifs==1);
}
