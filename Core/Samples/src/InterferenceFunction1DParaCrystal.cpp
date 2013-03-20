// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/InterferenceFunction1DParaCrystal.cpp
//! @brief     Implements class InterferenceFunction1DParaCrystal.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#include "InterferenceFunction1DParaCrystal.h"

InterferenceFunction1DParaCrystal::InterferenceFunction1DParaCrystal(double peak_distance, double width, double corr_length)
: m_peak_distance(peak_distance)
, m_width(width)
, m_corr_length(corr_length)
, m_use_corr_length(true)
{
    setName("InterferenceFunction1DParaCrystal");
	if (m_corr_length==0.0) {
		m_use_corr_length = false;
	}
    init_parameters();
}

void InterferenceFunction1DParaCrystal::init_parameters()
{
    getParameterPool()->clear();
    getParameterPool()->registerParameter("peak_distance", &m_peak_distance);
    getParameterPool()->registerParameter("width", &m_width);
    getParameterPool()->registerParameter("corr_length", &m_corr_length);
}

double InterferenceFunction1DParaCrystal::evaluate(const cvector_t &q) const
{
    double qxr = q.x().real();
    double qyr = q.y().real();
    double qpar = std::sqrt(qxr*qxr + qyr*qyr);
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
