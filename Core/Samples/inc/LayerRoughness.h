// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/LayerRoughness.h
//! @brief     Defines class LayerRoughness.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef LAYERROUGHNESS_H
#define LAYERROUGHNESS_H

#include "Types.h"
#include "IRoughness.h"

//! @class LayerRoughness
//! @brief Roughness of interface between two layers.
//!
//! Based on the article
//! D.K.G. de Boer, Physical review B, Volume 51, Number 8, 15 February 1995
//! "X-ray reflection and transmission by rough surfaces"
//! See Appendix A2

class LayerRoughness : public IRoughness
{
 public:
    LayerRoughness();
    LayerRoughness(double sigma, double hurstParameter, double latteralCorrLength);

    LayerRoughness *clone() const;

    //! return power spectral density of the surface roughness
    double getSpectralFun(const kvector_t &kvec) const;

    double getCorrFun(const kvector_t &k) const;

    //! set rms value of roughness
    inline void   setSigma(double sigma) { m_sigma = sigma; }
    //! return rms value of roughness
    inline double getSigma() const { return m_sigma; }

    //! Set hurst parameter. It describes how jagged the surface is.
    inline void   setHurstParameter(double hurstParameter) { m_hurstParameter = hurstParameter; }
    //! return hurst parameter
    inline double getHurstParameter() const { return m_hurstParameter; }

    //! set lateral correlation length
    inline void   setLatteralCorrLength(double latteralCorrLength) { m_latteralCorrLength = latteralCorrLength; }
    //! return latteral correlation length
    inline double getLatteralCorrLength() const { return m_latteralCorrLength; }

    //! print class
    friend std::ostream &operator<<(std::ostream &ostr, const LayerRoughness &m) { m.print(ostr); return ostr; }

 protected:
    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

    //! print class
    void print(std::ostream &ostr) const;

    double m_sigma;                //!< rms of roughness
    double m_hurstParameter;       //!< Hurst parameter which describes how jagged the interface, 0<H<=1
    double m_latteralCorrLength;   //!< latteral correlation length of the roughness
};

#endif // LAYERROUGHNESS_H
