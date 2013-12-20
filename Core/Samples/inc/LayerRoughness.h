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
//! @ingroup samples
//! @brief A Roughness of interface between two layers.
//!
//! Based on the article
//! D.K.G. de Boer, Physical review B, Volume 51, Number 8, 15 February 1995
//! "X-ray reflection and transmission by rough surfaces"

class BA_CORE_API_ LayerRoughness : public IRoughness
{
public:
    LayerRoughness();
    LayerRoughness(double sigma, double hurstParameter, double latteralCorrLength);

    LayerRoughness *clone() const;

    //! Calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    //! Returns power spectral density of the surface roughness
    double getSpectralFun(const kvector_t& kvec) const;

    double getCorrFun(const kvector_t& k) const;

    //! Sets rms of roughness
    inline void   setSigma(double sigma) { m_sigma = sigma; }
    //! Returns rms of roughness
    inline double getSigma() const { return m_sigma; }

    //! Sets hurst parameter. It describes how jagged the surface is.
    inline void   setHurstParameter(double hurstParameter) { m_hurstParameter = hurstParameter; }
    //! Returns hurst parameter
    inline double getHurstParameter() const { return m_hurstParameter; }

    //! Sets lateral correlation length
    inline void   setLatteralCorrLength(double latteralCorrLength) { m_latteralCorrLength = latteralCorrLength; }
    //! Returns latteral correlation length
    inline double getLatteralCorrLength() const { return m_latteralCorrLength; }

    //! Prints class
    friend std::ostream& operator<<(std::ostream& ostr, /*const*/ LayerRoughness& m)
    { m.print(ostr); return ostr; }

protected:
    //! Registers some class members for later access via parameter pool
    virtual void init_parameters();

    //! Prints class
    void print(std::ostream& ostr) const;

    double m_sigma;                //!< rms of roughness
    double m_hurstParameter;       //!< Hurst parameter which describes how jagged the interface, 0<H<=1
    double m_latteralCorrLength;   //!< latteral correlation length of the roughness
};

#endif // LAYERROUGHNESS_H


