// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/FormFactorDWBA.h
//! @brief     Defines class FormFactorDWBA.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORDWBA_H
#define FORMFACTORDWBA_H

#include "IFormFactorDecorator.h"

class ILayerRTCoefficients;

//! Evaluates the coherent sum of the four DWBA terms in a scalar IFormFactorDecorator.
//! @ingroup formfactors_internal

class BA_CORE_API_ FormFactorDWBA: public IFormFactorDecorator
{
public:
    FormFactorDWBA(const IFormFactor& form_factor);
    ~FormFactorDWBA() final {}

    FormFactorDWBA* clone() const final;

    void accept(ISampleVisitor* visitor) const final { visitor->visit(this); }

    //! Sets reflection/transmission info for scalar DWBA simulation
    void setSpecularInfo (const ILayerRTCoefficients* p_in_coeffs,
                          const ILayerRTCoefficients* p_out_coeffs);

    complex_t evaluate(const WavevectorInfo& wavevectors) const final;

    friend class TestPolarizedDWBATerms;

private:
    void calculateTerms(const WavevectorInfo& wavevectors) const;

    const ILayerRTCoefficients* mp_in_coeffs;  //!< not owned by this
    const ILayerRTCoefficients* mp_out_coeffs; //!< not owned by this
};

#endif // FORMFACTORDWBA_H
