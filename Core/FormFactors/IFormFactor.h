// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/FormFactors/IFormFactor.h
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

#include "Complex.h"
#include "Units.h"
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

    virtual IFormFactor* clone() const=0;

    //! @{ \internal
    virtual void accept(ISampleVisitor* visitor) const;
    //! @}

    //! Passes the refractive index of the ambient material in which this particle is embedded.
    virtual void setAmbientMaterial(const class IMaterial&) {}

    //! Returns scattering amplitude for complex wavevector bin
    virtual complex_t evaluate(const WavevectorInfo& wavevectors) const=0;

#ifndef SWIG
    //! Returns scattering amplitude for matrix interactions
    virtual Eigen::Matrix2cd evaluatePol(const WavevectorInfo& wavevectors) const;
#endif

    //! Returns the total volume of the particle of this form factor's shape
    virtual double getVolume() const;

    //! Returns the (approximate in some cases) radial size of the particle of this
    //! form factor's shape. This is used for SSCA calculations
    virtual double getRadius() const=0;

    //! Sets reflection/transmission info
    virtual void setSpecularInfo(const ILayerRTCoefficients*, const ILayerRTCoefficients*) {}
};

inline void IFormFactor::accept(ISampleVisitor* visitor) const
{
    visitor->visit(this);
}

#ifndef SWIG
inline Eigen::Matrix2cd IFormFactor::evaluatePol(const WavevectorInfo&) const
{
    // Throws to prevent unanticipated behaviour
    throw Exceptions::NotImplementedException(
        "IFormFactor::evaluatePol: is not implemented by default");
}
#endif

inline double IFormFactor::getVolume() const
{
    WavevectorInfo zero_wavevectors;
    return std::abs(evaluate(zero_wavevectors));
}

#endif // IFORMFACTOR_H
