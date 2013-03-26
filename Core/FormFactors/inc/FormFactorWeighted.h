// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorWeighted.h
//! @brief     Defines class FormFactorWeighted.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef FORMFACTORWEIGHTED_H_
#define FORMFACTORWEIGHTED_H_

#include "IFormFactor.h"

//! ?

class FormFactorWeighted : public IFormFactor
{
 public:
    FormFactorWeighted();
    virtual ~FormFactorWeighted();
    virtual FormFactorWeighted *clone() const;

    void addFormFactor(const IFormFactor &form_factor, double weight=1.0);

    virtual void setAmbientRefractiveIndex(const complex_t &refractive_index);

    virtual complex_t evaluate(const cvector_t &k_i, const Bin1DCVector &k_f_bin, double alpha_i, double alpha_f) const;

    virtual int getNumberOfStochasticParameters() const;

 protected:
    std::vector<IFormFactor *> m_form_factors;
    std::vector<double> m_weights;
};

#endif /* FORMFACTORWEIGHTED_H_ */
