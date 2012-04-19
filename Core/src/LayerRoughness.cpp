#include "LayerRoughness.h"
#include <math.h>


LayerRoughness::LayerRoughness() : m_sigma(0), m_hurstParameter(0), m_latteralCorrLength(0)
{

}


LayerRoughness::LayerRoughness(double sigma, double hurstParameter, double latteralCorrLength) :
    m_sigma(sigma), m_hurstParameter(hurstParameter), m_latteralCorrLength(latteralCorrLength)
{

}


/* ************************************************************************* */
//! Power spectral density of the surface roughness is a result of two-dimensional
//! Fourier transform of the correlation function of the roughness profile.
//!
//! Based on the article
//! D.K.G. de Boer, Physical review B, Volume 51, Number 8, 15 February 1995
//! "X-ray reflection and transmission by rough surfaces"
/* ************************************************************************* */
double LayerRoughness::getPowerSpectralDensity(const kvector_t &kvec)
{
    double H = m_hurstParameter;
    double xsi = m_latteralCorrLength;
    double Qpar2 = kvec.x()*kvec.x() + kvec.y()*kvec.y();
    return 4.0*M_PI*H * m_sigma*m_sigma * xsi*xsi * std::pow( (1.0 + Qpar2*xsi*xsi), (-1-H) );
}

