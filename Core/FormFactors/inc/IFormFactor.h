// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/IFormFactor.h
//! @brief     Defines and implements pure virtual interface IFormFactor.
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
    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this);}
    //! @}

    //! Passes the refractive index of the ambient material in which this
    //! particle is embedded.
    virtual void setAmbientMaterial(const IMaterial& material) {
        (void)material;
    }

    //! Returns scattering amplitude for complex wavevector bin
    //! @param k_i   incoming wavevector
    //! @param k_f_bin   outgoing wavevector bin
    virtual complex_t evaluate(const WavevectorInfo& wavevectors) const=0;

#ifndef GCCXML_SKIP_THIS
    //! Returns scattering amplitude for matrix interactions
    //! @param k_i   incoming wavevector
    //! @param k_f_bin   outgoing wavevector bin
    virtual Eigen::Matrix2cd evaluatePol(const WavevectorInfo& wavevectors) const;
#endif

    //! Returns the total volume of the particle of this form factor's shape
    virtual double getVolume() const;

    //! Returns the total radial size of the particle of this form factor's shape
    //! The default implementation returns the radius of a sphere with volume getVolume()
    virtual double getRadius() const;

    //! Sets reflection/transmission info
    virtual void setSpecularInfo(const ILayerRTCoefficients *p_in_coeffs,
                         const ILayerRTCoefficients *p_out_coeffs) {
        (void)p_in_coeffs;
        (void)p_out_coeffs;
    }
};

#ifndef GCCXML_SKIP_THIS
inline Eigen::Matrix2cd IFormFactor::evaluatePol(const WavevectorInfo&) const
{
    // Throws to prevent unanticipated behaviour
    throw NotImplementedException("IFormFactor::evaluatePol:"
            " is not implemented by default");
}
#endif

inline double IFormFactor::getVolume() const
{
    WavevectorInfo zero_wavevectors;
    return std::abs(evaluate(zero_wavevectors));
}

inline double IFormFactor::getRadius() const
{
    return std::pow(3.0*getVolume()/Units::PI/4.0, 1.0/3.0);
}

#endif // IFORMFACTOR_H


