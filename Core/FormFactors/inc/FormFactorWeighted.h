#ifndef FORMFACTORWEIGHTED_H_
#define FORMFACTORWEIGHTED_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   FormFactorWeighted.h
//! @brief  Definition of FormFactorWeighted
//! @author Scientific Computing Group at FRM II
//! @date   Jul 17, 2012

#include "IFormFactor.h"

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
