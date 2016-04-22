// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/IFormFactor.h
//! @brief     Declares and implements pure virtual interface IFormFactor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IFORMFACTOR_H
#define IFORMFACTOR_H

#include "Units.h"
#include "IMaterial.h"
#include "ISample.h"
#include "Bin.h"
#include "EigenCore.h"
#include "WavevectorInfo.h"

class ILayerRTCoefficients;

//! @class IFormFactor
//! @ingroup formfactors_internal
//! @brief The basic interface for form factors.

class BA_CORE_API_ IFormFactor : public ISample
{
public:
    IFormFactor() {}
    virtual ~IFormFactor() {}

    virtual IFormFactor *clone() const=0;

    //! @{ \internal
    virtual void accept(ISampleVisitor *visitor) const;
    //! @}

    //! Passes the refractive index of the ambient material in which this
    //! particle is embedded.
    virtual void setAmbientMaterial(const IMaterial&) {}

    //! Returns scattering amplitude for complex wavevector bin
    //! @param k_i   incoming wavevector
    //! @param k_f_bin   outgoing wavevector bin
    virtual complex_t evaluate(const WavevectorInfo& wavevectors) const=0;

#ifndef SWIG
    //! Returns scattering amplitude for matrix interactions
    //! @param k_i   incoming wavevector
    //! @param k_f_bin   outgoing wavevector bin
    virtual Eigen::Matrix2cd evaluatePol(const WavevectorInfo& wavevectors) const;
#endif

    //! Returns the total volume of the particle of this form factor's shape
    virtual double getVolume() const;

    //! Returns the (approximate in some cases) radial size of the particle of this
    //! form factor's shape. This is used for SSCA calculations
    virtual double getRadius() const=0;

    //! Sets reflection/transmission info
    virtual void setSpecularInfo(const ILayerRTCoefficients *p_in_coeffs,
                         const ILayerRTCoefficients *p_out_coeffs);
};

inline void IFormFactor::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}

#ifndef SWIG
inline Eigen::Matrix2cd IFormFactor::evaluatePol(const WavevectorInfo&) const
{
    // Throws to prevent unanticipated behaviour
    throw NotImplementedException("IFormFactor::evaluatePol: is not implemented by default");
}
#endif

inline double IFormFactor::getVolume() const
{
    WavevectorInfo zero_wavevectors;
    return std::abs(evaluate(zero_wavevectors));
}

inline void IFormFactor::setSpecularInfo(const ILayerRTCoefficients *p_in_coeffs,
                                         const ILayerRTCoefficients *p_out_coeffs)
{
    (void)p_in_coeffs;
    (void)p_out_coeffs;
}

#endif // IFORMFACTOR_H
