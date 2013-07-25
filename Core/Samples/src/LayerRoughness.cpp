// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/LayerRoughness.cpp
//! @brief     Implements class LayerRoughness.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "LayerRoughness.h"
#include <cmath>
#include <iostream>
#include <iomanip>

LayerRoughness::LayerRoughness()
: m_sigma(0)
, m_hurstParameter(0)
, m_latteralCorrLength(0)
{
    setName("Roughness");
    init_parameters();
}

LayerRoughness::LayerRoughness(double sigma, double hurstParameter, double latteralCorrLength)
: m_sigma(sigma)
, m_hurstParameter(hurstParameter)
, m_latteralCorrLength(latteralCorrLength)
{
    setName("roughness");
    init_parameters();
}

LayerRoughness *LayerRoughness::clone() const
{
    return new LayerRoughness(m_sigma, m_hurstParameter, m_latteralCorrLength);
}

void LayerRoughness::init_parameters()
{
    clearParameterPool();
    registerParameter("sigma", &m_sigma);
    registerParameter("hurst", &m_hurstParameter);
    registerParameter("corrlength", &m_latteralCorrLength);
}


/* ************************************************************************* */
//! Power spectral density of the surface roughness is a result of two-dimensional
//! Fourier transform of the correlation function of the roughness profile.
//!
//! Based on the article
//! D.K.G. de Boer, Physical review B, Volume 51, Number 8, 15 February 1995
//! "X-ray reflection and transmission by rough surfaces"
/* ************************************************************************* */
double LayerRoughness::getSpectralFun(const kvector_t& kvec) const
{
    double H = m_hurstParameter;
    double clength2 = m_latteralCorrLength*m_latteralCorrLength;
    double Qpar2 = kvec.x()*kvec.x() + kvec.y()*kvec.y();
    return 4.0*M_PI*H * m_sigma*m_sigma * clength2 * std::pow( (1.0 + Qpar2*clength2), (-1-H) );
}

//! Correlation function of the roughness profile

double LayerRoughness::getCorrFun(const kvector_t& k) const
{
    double H = m_hurstParameter;
    double clength = m_latteralCorrLength;
    double R = sqrt(k.x()*k.x() + k.y()*k.y());
    return m_sigma*m_sigma*std::exp( -1.0*std::pow(R/clength, 2.*H) );
}

void LayerRoughness::print(std::ostream& ostr) const
{
    ISample::print(ostr);
    ostr << "-->LayerRoughness{ sigma=" << m_sigma << "}";
}


