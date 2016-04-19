// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/FormFactorDWBA.h
//! @brief     Defines class FormFactorDWBA.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORDWBA_H_
#define FORMFACTORDWBA_H_

#include "IFormFactorDecorator.h"
#include "LayerSpecularInfo.h"

//! @class FormFactorDWBA
//! @ingroup formfactors_internal
//! @brief Evaluates a coherent sum of the four DWBA terms in a scalar formfactor.

class BA_CORE_API_ FormFactorDWBA: public IFormFactorDecorator
{
public:
    FormFactorDWBA(const IFormFactor& form_factor);
    virtual ~FormFactorDWBA();

    virtual FormFactorDWBA *clone() const;

    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    //! Sets reflection/transmission info for scalar DWBA simulation
    virtual void setSpecularInfo(const ILayerRTCoefficients *p_in_coeffs,
                         const ILayerRTCoefficients *p_out_coeffs);

    virtual complex_t evaluate(const WavevectorInfo& wavevectors) const;

    friend class TestPolarizedDWBATerms;

protected:
    void calculateTerms(const WavevectorInfo& wavevectors) const;

    mutable complex_t m_term_S, m_term_RS, m_term_SR, m_term_RSR;
    const ILayerRTCoefficients *mp_in_coeffs;
    const ILayerRTCoefficients *mp_out_coeffs;
};

#endif /* FORMFACTORDWBA_H_ */


