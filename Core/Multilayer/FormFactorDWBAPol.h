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
#include <memory>

class ILayerRTCoefficients;

//! Evaluates the coherent sum of the 16 matrix DWBA terms in a polarized IFormFactor.

//! @ingroup formfactors_internal

class FormFactorDWBAPol final : public IFormFactor
{
public:
    FormFactorDWBAPol(const IFormFactor& form_factor);
    ~FormFactorDWBAPol() override;

    FormFactorDWBAPol* clone() const override;

    void accept(INodeVisitor* visitor) const override { visitor->visit(this); }

    //! Throws not-implemented exception
    complex_t evaluate(const WavevectorInfo& wavevectors) const override;

    //! Calculates and returns a polarized form factor calculation in DWBA
    Eigen::Matrix2cd evaluatePol(const WavevectorInfo& wavevectors) const override;

    double getVolume() const override { return mP_form_factor->getVolume(); }

    double getRadialExtension() const override { return mP_form_factor->getRadialExtension(); }

    double bottomZ(const IRotation& rotation) const override;

    void setSpecularInfo(const ILayerRTCoefficients* p_in_coeffs,
                         const ILayerRTCoefficients* p_out_coeffs) override;

    friend class TestPolarizedDWBATerms;

private:
    //! The form factor for BA
    std::unique_ptr<IFormFactor> mP_form_factor;

    const ILayerRTCoefficients* mp_in_coeffs;  //!< not owned by this
    const ILayerRTCoefficients* mp_out_coeffs; //!< not owned by this
};

#endif // FORMFACTORDWBAPOL_H
