#ifndef WEIGHTEDFORMFACTOR_H_
#define WEIGHTEDFORMFACTOR_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   WeightedFormFactor.h
//! @brief  Definition of
//! @author Scientific Computing Group at FRM II
//! @date   Jul 17, 2012

#include "IFormFactor.h"

class WeightedFormFactor : public IFormFactor
{
public:
    WeightedFormFactor();
    virtual ~WeightedFormFactor();
    virtual WeightedFormFactor *clone() const;

    void addFormFactor(const IFormFactor &form_factor, double weight=1.0);

    virtual void setAmbientRefractiveIndex(complex_t refractive_index);

    virtual complex_t evaluate(kvector_t k_i, kvector_t k_f) const;

    virtual complex_t evaluateForComplexkz(kvector_t k_i, kvector_t k_f, complex_t k_iz, complex_t k_fz) const;

    virtual int getNumberOfStochasticParameters() const;
protected:
    std::vector<IFormFactor *> m_form_factors;
    std::vector<double> m_weights;
};


#endif /* WEIGHTEDFORMFACTOR_H_ */
