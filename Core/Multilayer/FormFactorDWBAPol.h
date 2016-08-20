// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/FormFactorDWBAPol.h
//! @brief     Defines class FormFactorDWBAPol.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORDWBAPOL_H
#define FORMFACTORDWBAPOL_H

#include "IFormFactor.h"

class ILayerRTCoefficients;

//! Evaluates the coherent sum of the 16 matrix DWBA terms in a polarized IFormFactor.
//! @ingroup formfactors_internal

class BA_CORE_API_ FormFactorDWBAPol : public IFormFactor
{
public:
    FormFactorDWBAPol(const IFormFactor& form_factor);
    virtual ~FormFactorDWBAPol();

    FormFactorDWBAPol* clone() const final;

    void accept(ISampleVisitor* visitor) const final { visitor->visit(this); }

    //! Throws not-implemented exception
    complex_t evaluate(const WavevectorInfo& wavevectors) const final;

    //! Calculates and returns a polarized form factor calculation in DWBA
    Eigen::Matrix2cd evaluatePol(const WavevectorInfo& wavevectors) const final;

    //! Returns the total volume of the particle of this form factor's shape
    double getVolume() const final { return mp_form_factor->getVolume(); }

    //! Returns the (approximate in some cases) radial size of the particle of this
    //! form factor's shape. This is used for SSCA calculations
    double getRadialExtension() const final { return mp_form_factor->getRadialExtension(); }

    //! Sets reflection/transmission info for scalar DWBA simulation
    void setSpecularInfo(const ILayerRTCoefficients* p_in_coeffs,
                         const ILayerRTCoefficients* p_out_coeffs);

    friend class TestPolarizedDWBATerms;

protected:
    void calculateTerms(const WavevectorInfo& wavevectors) const;

    //! The matrix form factor for BA
    IFormFactor* mp_form_factor;

    const ILayerRTCoefficients* mp_in_coeffs;
    const ILayerRTCoefficients* mp_out_coeffs;
};

#endif // FORMFACTORDWBAPOL_H
