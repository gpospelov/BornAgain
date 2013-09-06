// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorDWBA.h
//! @brief     Defines class FormFactorDWBA.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORDWBA_H_
#define FORMFACTORDWBA_H_

#include "IFormFactorDecorator.h"
#include "LayerSpecularInfo.h"

//! Evaluates a coherent sum of the four DWBA terms in a scalar form factor

class FormFactorDWBA: public IFormFactorDecorator
{
public:
    FormFactorDWBA(IFormFactor* p_form_factor);
    virtual ~FormFactorDWBA();

    virtual FormFactorDWBA *clone() const;

    //! Sets reflection/transmission info for scalar DWBA simulation
    void setSpecularInfo(const LayerSpecularInfo& layer_specular_info);

    virtual complex_t evaluate(const cvector_t& k_i, const Bin1DCVector&
            k_f_bin, double alpha_i, double alpha_f) const;

    friend class TestPolarizedDWBATerms;

protected:
    const ILayerRTCoefficients *getOutCoeffs(double alpha_f) const;
    void calculateTerms(const cvector_t& k_i, const Bin1DCVector& k_f_bin,
            double alpha_i, double alpha_f) const;

    LayerSpecularInfo *mp_specular_info;

    mutable complex_t m_term_S, m_term_RS, m_term_SR, m_term_RSR;
};

inline const ILayerRTCoefficients* FormFactorDWBA::getOutCoeffs(
        double alpha) const {
    return mp_specular_info->getOutCoefficients(alpha, 0.0);
}

#endif /* FORMFACTORDWBA_H_ */


