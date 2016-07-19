// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/LayerRoughness.h
//! @brief     Declares class LayerRoughness.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef LAYERROUGHNESS_H
#define LAYERROUGHNESS_H

#include "IRoughness.h"
#include "Vectors3D.h"

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
    virtual void accept(ISampleVisitor *visitor) const
    {
        visitor->visit(this);
    }

    //! Returns power spectral density of the surface roughness
    double getSpectralFun(const kvector_t kvec) const;

    double getCorrFun(const kvector_t k) const;

    //! Sets rms of roughness
    void setSigma(double sigma);
    //! Returns rms of roughness
    double getSigma() const;

    //! Sets hurst parameter. It describes how jagged the surface is.
    void setHurstParameter(double hurstParameter);
    //! Returns hurst parameter
    double getHurstParameter() const;

    //! Sets lateral correlation length
    void setLatteralCorrLength(double latteralCorrLength);
    //! Returns latteral correlation length
    double getLatteralCorrLength() const;

    //! Prints class
    friend std::ostream& operator<<(std::ostream& ostr, /*const*/ LayerRoughness& m);

protected:
    //! Registers some class members for later access via parameter pool
    virtual void init_parameters();

    //! Prints class
    void print(std::ostream& ostr) const;

    double m_sigma;                //!< rms of roughness
    double m_hurstParameter;   //!< Hurst parameter which describes how jagged the interface, 0<H<=1
    double m_latteralCorrLength;   //!< latteral correlation length of the roughness
private:
    void initialize();
};

#endif // LAYERROUGHNESS_H
