#include "LocalMonodisperseApproximationStrategy.h"
#include "Exceptions.h"

LocalMonodisperseApproximationStrategy::LocalMonodisperseApproximationStrategy()
{
}

void LocalMonodisperseApproximationStrategy::init(
        const SafePointerVector<FormFactorInfo> &form_factor_infos,
        const SafePointerVector<IInterferenceFunction> &ifs)
{
    IInterferenceFunctionStrategy::init(form_factor_infos, ifs);
    if (!checkVectorSizes()) {
        throw ClassInitializationException("Wrong number of formfactors or interference functions for Decoupling Approximation.");
    }
}

double LocalMonodisperseApproximationStrategy::evaluate(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin, double alpha_i, double alpha_f) const
{
    double intensity = 0.0;
    for (size_t i=0; i<m_ff_infos.size(); ++i) {
        complex_t ff = m_ff_infos[i]->mp_ff->evaluate(k_i, k_f_bin, alpha_i, alpha_f);
        double itf_function = m_ifs[i]->evaluate(k_i-k_f_bin.getMidPoint());
        double fraction = m_ff_infos[i]->m_abundance;
        intensity += fraction*(itf_function*std::norm(ff));
    }
    return intensity;
}

bool LocalMonodisperseApproximationStrategy::checkVectorSizes()
{
    size_t n_ffs = m_ff_infos.size();
    size_t n_ifs = m_ifs.size();
    return (n_ffs>0 && n_ifs==n_ffs);
}
