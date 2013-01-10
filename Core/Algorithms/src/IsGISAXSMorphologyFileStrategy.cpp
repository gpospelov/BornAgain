#include "IsGISAXSMorphologyFileStrategy.h"

#include <algorithm>

IsGISAXSMorphologyFileStrategy::IsGISAXSMorphologyFileStrategy()
: m_win_x(0.0)
, m_win_y(0.0)
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

void IsGISAXSMorphologyFileStrategy::initPositions(
        const std::vector<double> &x_positions, const std::vector<double> &y_positions)
{
    m_x_positions = x_positions;
    m_y_positions = y_positions;
    // init window sizes for Hann function
    double x_min = *std::min_element(m_x_positions.begin(), m_x_positions.end());
    double x_max = *std::max_element(m_x_positions.begin(), m_x_positions.end());
    double y_min = *std::min_element(m_y_positions.begin(), m_y_positions.end());
    double y_max = *std::max_element(m_y_positions.begin(), m_y_positions.end());
    m_win_x = x_max - x_min;
    m_win_y = y_max - y_min;
    if (m_win_x <= 0.0 || m_win_y <= 0.0) {
        throw Exceptions::ClassInitializationException("Window sizes should be strictly positive");
    }
}

double IsGISAXSMorphologyFileStrategy::evaluate(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin, double alpha_i, double alpha_f) const
{
    cvector_t q = k_i - k_f_bin.getMidPoint();
    // calculate form factors
    std::vector<complex_t> ff_values;
    for (size_t i=0; i<m_form_factors.size(); ++i) {
        ff_values.push_back(m_form_factors[i]->evaluate(k_i, k_f_bin, alpha_i, alpha_f));
    }

    // coherent part
    complex_t coherent_amplitude = complex_t(0.0, 0.0);
    for (size_t i=0; i<m_form_factors.size(); ++i) {
        complex_t phase = q.x()*m_x_positions[i] + q.y()*m_y_positions[i];
        double fraction = m_fractions[i];
        double hann_value = hannFunction(m_x_positions[i], m_y_positions[i]);
        coherent_amplitude += fraction*ff_values[i]*std::exp( complex_t(0.0, 1.0)*phase )*hann_value;
    }
    double coherent_intensity = std::norm(coherent_amplitude);

    // diffuse part
    double diffuse_intensity = 0.0;
    for (size_t i=0; i<m_form_factors.size(); ++i) {
        diffuse_intensity += m_fractions[i]*std::norm(ff_values[i]);
        for (size_t j=i+1; j<m_form_factors.size(); ++j) {
            double x_diff = m_x_positions[i]-m_x_positions[j];
            double y_diff = m_y_positions[i]-m_y_positions[j];
            complex_t phase = q.x()*x_diff + q.y()*y_diff;
            diffuse_intensity += m_fractions[i]*m_fractions[j]*2.0*(ff_values[i]*std::conj(ff_values[j])*std::exp( complex_t(0.0, 1.0)*phase )).real();
        }
    }
    return coherent_intensity + diffuse_intensity;
}

bool IsGISAXSMorphologyFileStrategy::checkVectorSizes()
{
    size_t n_ffs = m_form_factors.size();
    size_t n_frs = m_fractions.size();
    size_t n_ifs = m_interference_functions.size();
    return (n_ffs==n_frs && n_ifs==0);
}

double IsGISAXSMorphologyFileStrategy::hannFunction(double x, double y) const
{
    double result = (M_PI*M_PI/4.0)*std::cos(M_PI*x/m_win_x)*std::cos(M_PI*y/m_win_y);
    return result;
}
