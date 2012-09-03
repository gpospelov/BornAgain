#ifndef IFORMFACTOR_H
#define IFORMFACTOR_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   IFormFactor.h
//! @brief  Definition of IFormFactor and IBornFormFactor
//! @author Scientific Computing Group at FRM II
//! @date   01.04.2012

#include "Types.h"
#include "ISample.h"


//- -------------------------------------------------------------------
//! @class IFormFactor
//! @brief Definition of IFormfactor interface
//- -------------------------------------------------------------------
class IFormFactor : public ISample
{
public:
    IFormFactor(){}
    virtual ~IFormFactor() {}
    virtual IFormFactor *clone() const=0;

    virtual void setAmbientRefractiveIndex(complex_t refractive_index) { (void)refractive_index; }

    /// calculate scattering amplitude for complex wavevectors
    /// @param k_i   incoming wavevector
    /// @param k_f   outgoing wavevector
    virtual complex_t evaluate(cvector_t k_i, cvector_t k_f, double alpha_i, double alpha_f) const=0;

    /// calculate a possible diffuse scattering intensity
    /// @param k_i   incoming wavevector
    /// @param k_f   outgoing wavevector
    virtual double evaluateDiffuse(cvector_t k_i, cvector_t k_f, double alpha_i, double alpha_f) const;

    /// return number of variable/stochastic parameters
    virtual int getNumberOfStochasticParameters() const { return 0; }

};

inline double IFormFactor::evaluateDiffuse(cvector_t k_i, cvector_t k_f, double alpha_i, double alpha_f) const
{
    (void)k_i;
    (void)k_f;
    (void)alpha_i;
    (void)alpha_f;
    return 0.0;
}


class IFormFactorDecorator : public IFormFactor
{
public:
    IFormFactorDecorator(IFormFactor *p_form_factor) : mp_form_factor(p_form_factor) {}
    virtual ~IFormFactorDecorator() {}
    virtual IFormFactorDecorator *clone() const=0;

    virtual void setAmbientRefractiveIndex(complex_t refractive_index) { if (mp_form_factor) mp_form_factor->setAmbientRefractiveIndex(refractive_index); }
protected:
    IFormFactor *mp_form_factor;
};

class IBornFormFactor : public IFormFactor
{
public:
    IBornFormFactor(){}
    virtual ~IBornFormFactor() {}
	virtual IBornFormFactor *clone() const=0;

	virtual complex_t evaluate(cvector_t k_i, cvector_t k_f, double alpha_i, double alpha_f) const;
protected:
    /// evaluate scattering amplitude for complex wavevector
    /// @param q  wavevector transfer \f$q\equiv k_i-k_f\f$
    virtual complex_t evaluate_for_q(cvector_t q) const=0;
};

inline complex_t IBornFormFactor::evaluate(cvector_t k_i, cvector_t k_f, double alpha_i, double alpha_f) const
{
    (void)alpha_i;
    (void)alpha_f;
    return evaluate_for_q(k_i - k_f);
}

#endif // IFORMFACTOR_H
