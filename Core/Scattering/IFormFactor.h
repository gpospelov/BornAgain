// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Scattering/IFormFactor.h
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

#include "ISample.h"
#include "Complex.h"
#include "EigenCore.h"
#include "Vectors3D.h"
#include "ZLimits.h"

class HomogeneousMaterial;
class ILayerRTCoefficients;
class IRotation;
class WavevectorInfo;

//! Pure virtual base class for all form factors.
//!
//! The actual form factor is returned by the complex valued function IFormFactor::evaluate,
//! which depends on the incoming and outgoing wave vectors ki and kf.
//! If it only depends on the scattering vector q=ki-kf, then it is a IBornFormFactor.
//!
//! Other children besides IBornFormFactor are IFormFactorDecorator, FormFactorWeighted,
//! FormFactorDWBA, FormFactorDWBAPol and FormFactorCrystal.

//! @ingroup formfactors_internal

class BA_CORE_API_ IFormFactor : public ISample
{
public:
    IFormFactor() {}
    ~IFormFactor() override;
    IFormFactor* clone() const override=0;

    //! Creates a (possibly sliced) form factor with the given rotation and translation
    IFormFactor* createSlicedFormFactor(ZLimits limits, const IRotation& rot,
                                        kvector_t translation) const;

    //! Passes the refractive index of the ambient material in which this particle is embedded.
    virtual void setAmbientMaterial(const HomogeneousMaterial&) =0;

    //! Returns scattering amplitude for complex wavevectors ki, kf.
    virtual complex_t evaluate(const WavevectorInfo& wavevectors) const=0;

#ifndef SWIG
    //! Returns scattering amplitude for matrix interactions
    virtual Eigen::Matrix2cd evaluatePol(const WavevectorInfo& wavevectors) const;
#endif

    //! Returns the total volume of the particle of this form factor's shape
    virtual double getVolume() const;

    //! Returns the (approximate in some cases) radial size of the particle of this
    //! form factor's shape. This is used for SSCA calculations
    virtual double getRadialExtension() const=0;

    //! Returns the z-coordinate of the lowest point in this shape after a given rotation
    virtual double bottomZ(const IRotation& rotation) const=0;

    //! Returns the z-coordinate of the lowest point in this shape after a given rotation
    virtual double topZ(const IRotation& rotation) const=0;

    //! Sets reflection/transmission info
    virtual void setSpecularInfo(const ILayerRTCoefficients*, const ILayerRTCoefficients*) {}

protected:
    //! Checks if slicing has a fast analytical solution
    virtual bool canSliceAnalytically(const IRotation& rot) const;

    //! Actually slices the form factor or throws an exception
    virtual IFormFactor* sliceFormFactor(ZLimits limits, const IRotation& rot,
                                         kvector_t translation) const;
};

bool ShapeIsContainedInLimits(const IFormFactor& formfactor, ZLimits limits,
                              const IRotation& rot, kvector_t translation);

IFormFactor* CreateTransformedFormFactor(const IFormFactor& formfactor, const IRotation& rot,
                                         kvector_t translation);

#endif // IFORMFACTOR_H
