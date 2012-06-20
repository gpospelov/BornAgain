#include "InterferenceFunction1DParaCrystal.h"

InterferenceFunction1DParaCrystal::InterferenceFunction1DParaCrystal(double peak_distance, double width, double corr_length)
: m_peak_distance(peak_distance)
, m_width(width)
, m_corr_length(corr_length)
, m_use_corr_length(true)
{
	if (m_corr_length==0.0) {
		m_use_corr_length = false;
	}
}

double InterferenceFunction1DParaCrystal::evaluate(kvector_t q) const
{
	double qpar = q.magxy();
	complex_t p_transformed = FTGaussianCorrLength(qpar);
	double interference_function = 1.0 + 2*(p_transformed/(complex_t(1.0, 0.0)-p_transformed)).real();
	return interference_function;
}

complex_t InterferenceFunction1DParaCrystal::FTGaussianCorrLength(double qpar) const
{
	double exponent1 = -(m_width*m_width*qpar*qpar)/2.0;
	complex_t exponent2 = complex_t(0.0, 1.0)*qpar*m_peak_distance;
	complex_t result = std::exp(exponent2)*std::exp(exponent1);
	if (m_use_corr_length) {
		result *= std::exp(-m_peak_distance/m_corr_length);
	}
	return result;
}

