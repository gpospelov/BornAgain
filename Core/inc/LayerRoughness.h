#ifndef LAYERROUGHNESS_H
#define LAYERROUGHNESS_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   LayerRoughness.h
//! @brief  Definition of LayerRoughness class
//! @author Scientific Computing Group at FRM II
//! @date   01.04.2012

#include "Types.h"
#include "IRoughness.h"


//- -------------------------------------------------------------------
//! @class LayerRoughness
//! @brief Roughness of interface between two layers.
//!
//! Based on the article
//! D.K.G. de Boer, Physical review B, Volume 51, Number 8, 15 February 1995
//! "X-ray reflection and transmission by rough surfaces"
//! See Appendix A2
//- -------------------------------------------------------------------
class LayerRoughness : public IRoughness
{
public:
    LayerRoughness();
    LayerRoughness(double sigma, double hurstParameter, double latteralCorrLength);

    //! return power spectral density of the surface roughness
    double getSpectralFun(const kvector_t &kvec) const;

    double getCorrFun(const kvector_t &k) const;

    //! set rms value of roughness
    void   setSigma(double sigma) { m_sigma = sigma; }
    //! return rms value of roughness
    double getSigma() const { return m_sigma; }

    //! Set hurst parameter. It describes how jagged the surface is.
    inline void   setHurstParameter(double hurstParameter) { m_hurstParameter = hurstParameter; }
    //! return hurst parameter
    inline double getHurstParameter() const { return m_hurstParameter; }

    //! set lateral correlation length
    inline void   setLatteralCorrLength(double latteralCorrLength) { m_latteralCorrLength = latteralCorrLength; }
    //! return latteral correlation length
    inline double getLatteralCorrLength() const { return m_latteralCorrLength; }

protected:
    double m_sigma;                //!< rms of roughness
    double m_hurstParameter;       //!< Hurst parameter which describes how jagged the interface, 0<H<=1
    double m_latteralCorrLength;   //!< latteral correlation length of the roughness
};

#endif // LAYERROUGHNESS_H
