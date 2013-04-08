// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorDecoratorMultiPositionFactor.h
//! @brief     Defines class FormFactorDecoratorMultiPositionFactor.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORDECORATORMULTIPOSITIONFACTOR_H_
#define FORMFACTORDECORATORMULTIPOSITIONFACTOR_H_

#include "IFormFactorDecorator.h"

//! ?

class FormFactorDecoratorMultiPositionFactor : public IFormFactorDecorator
{
 public:
    FormFactorDecoratorMultiPositionFactor(const IFormFactor& form_factor, std::vector<kvector_t> positions);
    virtual ~FormFactorDecoratorMultiPositionFactor() {}
    virtual FormFactorDecoratorMultiPositionFactor *clone() const;

    virtual complex_t evaluate(const cvector_t& k_i, const Bin1DCVector& k_f_bin, double alpha_i, double alpha_f) const;

    virtual int getNumberOfStochasticParameters() const {
        return mp_form_factor->getNumberOfStochasticParameters();
    }

 private:
    complex_t getPositionsFactor(cvector_t q) const;
    std::vector<kvector_t> m_positions;
};

inline FormFactorDecoratorMultiPositionFactor::FormFactorDecoratorMultiPositionFactor(
        const IFormFactor& form_factor, std::vector<kvector_t> positions)
: IFormFactorDecorator(form_factor.clone())
, m_positions(positions)
{
    setName("FormFactorDecoratorMultiPositionFactor");
}

inline FormFactorDecoratorMultiPositionFactor* FormFactorDecoratorMultiPositionFactor::clone() const
{
    return new FormFactorDecoratorMultiPositionFactor(*mp_form_factor, m_positions);
}

inline complex_t FormFactorDecoratorMultiPositionFactor::evaluate(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin, double alpha_i, double alpha_f) const
{
    cvector_t q = k_i - k_f_bin.getMidPoint();
    return getPositionsFactor(q)*mp_form_factor->evaluate(k_i, k_f_bin, alpha_i, alpha_f);
}

inline complex_t FormFactorDecoratorMultiPositionFactor::getPositionsFactor(cvector_t q) const
{
    complex_t result;
    for (size_t i=0; i<m_positions.size(); ++i) {
        complex_t qr = q.x()*m_positions[i].x() + q.y()*m_positions[i].y() + q.z()*m_positions[i].z();
        result += std::exp(complex_t(0.0, 1.0)*qr);
    }
    return result;
}

#endif /* FORMFACTORDECORATORMULTIPOSITIONFACTOR_H_ */


