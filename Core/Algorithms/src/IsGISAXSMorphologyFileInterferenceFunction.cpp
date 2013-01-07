#include "IsGISAXSMorphologyFileInterferenceFunction.h"

#include <cmath>

IsGISAXSMorphologyFileInterferenceFunction::IsGISAXSMorphologyFileInterferenceFunction(
        double pos_x, double pos_y, double cutoff)
: m_pos_x(pos_x)
, m_pos_y(pos_y)
, m_cutoff(cutoff)
, m_hann_value(0.0)
{
    m_hann_value = hannFunction(pos_x, pos_y, cutoff);
}

double IsGISAXSMorphologyFileInterferenceFunction::evaluate(
        const cvector_t& q) const
{
    (void)q;
    return m_hann_value;
}

IsGISAXSMorphologyFileInterferenceFunction* IsGISAXSMorphologyFileInterferenceFunction::clone() const
{
    return new IsGISAXSMorphologyFileInterferenceFunction(m_pos_x, m_pos_y, m_cutoff);
}

double IsGISAXSMorphologyFileInterferenceFunction::hannFunction(double x,
        double y, double cutoff)
{
    if (cutoff <= 0.0) {
        throw Exceptions::ClassInitializationException("Cut-off radius should be strictly positive");
    }
    double result = (M_PI*M_PI/4.0)*std::cos(M_PI*x/cutoff)*std::cos(M_PI*y/cutoff);
    return result;
}
