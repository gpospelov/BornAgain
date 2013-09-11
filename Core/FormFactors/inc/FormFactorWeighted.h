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

//! Coherent sum of different form factors with different weights
//! (for scalar form factors)

class FormFactorWeighted : public IFormFactor
{
 public:
    FormFactorWeighted();
    virtual ~FormFactorWeighted();
    virtual FormFactorWeighted *clone() const;

    void addFormFactor(const IFormFactor& form_factor, double weight=1.0);

    virtual void setAmbientMaterial(const IMaterial *p_material);

    virtual complex_t evaluate(const cvector_t& k_i,
            const Bin1DCVector& k_f_bin, Bin1D alpha_f_bin) const;

    //! Calculates and returns a polarized form factor calculation in DWBA
    virtual Eigen::Matrix2cd evaluatePol(const cvector_t& k_i,
            const Bin1DCVector& k_f_bin, Bin1D alpha_f_bin,
            Bin1D phi_f_bin) const;

    virtual int getNumberOfStochasticParameters() const;

 protected:
    std::vector<IFormFactor *> m_form_factors;
    std::vector<double> m_weights;
};

#endif /* FORMFACTORWEIGHTED_H_ */


